/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:03:59 by julekgwa          #+#    #+#             */
/*   Updated: 2018/11/27 13:23:01 by junius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char  *ft_cmd_alias(char *cmd)
{
  if (EQUAL(cmd, "l") || EQUAL(cmd, "ll")) {
    return "ls";
  }

  return cmd;
}
