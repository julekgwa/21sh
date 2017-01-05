/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 01:39:54 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/03 09:55:46 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_hash_code(const char *key)
{
	unsigned int	sum;
	int				i;

	sum = 0;
	i = 0;
	while (key[i])
	{
		sum += (unsigned char)key[i] * (i + 1);
		i++;
	}
	return (sum % MAX_HASH);
}

void			ft_free_item(t_hash *item)
{
	free(item->key);
	if (item->value)
		free(item->value);
	if (item)
		free(item);
}

void			ft_delete_item(t_hash *table[], const char *key)
{
	t_hash	**link;
	t_hash	*tmp;

	link = &table[ft_hash_code(key)];
	while (*link)
	{
		tmp = *link;
		if (strcmp(tmp->key, key) == 0)
		{
			*link = tmp->next;
			ft_free_item(tmp);
			break ;
		}
		else
			link = &(*link)->next;
	}
}

t_hash			*ft_search(t_hash *head, const char *key)
{
	t_hash *cursor;

	cursor = head;
	while (cursor != NULL)
	{
		if (strcmp(cursor->key, key) == 0)
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

void			ft_insert_item(t_hash *hash[], const char *key, const char *val)
{
	unsigned int	code;
	t_hash			*item;

	code = ft_hash_code(key);
	item = (t_hash *)malloc(sizeof(*item));
	if (item != NULL)
	{
		if (ft_search(hash[code], key))
			ft_delete_item(hash, key);
		item->key = strdup(key);
		item->value = strdup(val);
		item->next = hash[code];
		hash[code] = item;
	}
}
