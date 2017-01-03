/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 20:46:22 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/27 21:04:44 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_hash_table(t_hash *table[])
{
	int		i;
	t_hash	*tmp;
	t_hash	*head;

	i = 0;
	while (i < MAX_HASH)
	{
		if (table[i])
		{
			head = table[i];
			while ((tmp = head) != NULL)
			{
				head = head->next;
				ft_delete_item(table, tmp->key);
			}
		}
		i++;
	}
}

void	ft_set_hash_table(int res, char *name, char **envp, t_stack *hist)
{
	char	*path;
	char	**split;
	char	*temp;

	if (!ft_strequ(name, "PATH"))
		return ;
	if (res != -1)
		return ;
	path = ft_get_env("$PATH", envp);
	temp = QUOTES(path);
	split = ft_strsplit(temp, ':');
	ft_hash_table_bin(hist->hash, split);
	freecopy(split);
}
