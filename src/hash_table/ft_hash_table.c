/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 01:39:54 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/24 01:48:48 by julekgwa         ###   ########.fr       */
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

void			ft_free_item(t_hash_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void			ft_delete_item(t_hash_item *table[], const char *key)
{
	t_hash_item	**link;

	link = &table[ft_hash_code(key)];
	while (*link)
	{
		t_hash_item *tmp = *link;
		if (strcmp(tmp->key, key) == 0)
		{
			*link = tmp->next;
			ft_free_item(tmp);
			break;
		}
		else
			link = &(*link)->next;
	}
}

t_hash_item		*ft_search(t_hash_item *head,const char *key)
{
	t_hash_item *cursor;

	cursor = head;
	while(cursor != NULL)
	{
		if (strcmp(cursor->key, key) == 0)
			return cursor;
		cursor = cursor->next;
	}
	return (NULL);
}

void			ft_insert_item(t_hash_item *table[], const char *key, const char *value)
{
	unsigned int	code;
	t_hash_item		*item;

	code = ft_hash_code(key);
	item = (t_hash_item *)malloc(sizeof(*item));
	if (item != NULL)
	{
		if (ft_search(table[code], key))
			ft_delete_item(table, key);
		item->key = strdup(key);
		item->value = strdup(value);
		item->next = table[code];
		table[code] = item;
	}
}

void			ft_display_hash_table(t_hash_item *table[])
{
	int			i;
	t_hash_item	*tmp;

	i = 0;
	while (i < MAX_HASH)
	{
		tmp = table[i];
		while (tmp)
		{
			ft_putstr(tmp->key);
			ft_putchar('=');
			ft_putendl(tmp->value);
			tmp = tmp->next;
		}
		i++;
	}
}
