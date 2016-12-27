/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 16:43:05 by julekgwa          #+#    #+#             */
/*   Updated: 2016/07/23 15:52:27 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char    *ft_search_token(const char *s)
{
    char *p;

    p = strchr(s + 1, '"');//search end '"'
    if (p)
        return  (p);//skip to '"'
    else
        return (NULL);
}

t_token    ft_return_null(const char **sp, const char *s, t_token token)
{
  *sp = s;
  return token;
}

t_token ft_get_token(const char **sp, char sep)
{
    const char *s;
    t_token token;

    memset(&token, 0, sizeof(t_token));
    s = *sp;
    while(*s && *s == sep)//skip top separators
        ++s;
    if(!*s)
      return ft_return_null(sp, s, token);
    token.top = s;
    while(*s && *s != sep)
    {
        if(*s == '\\')
            ++s;
        else if(*s == '"' && sep == ' ' && ft_search_token(s))
          s = ft_search_token(s);
        ++s;
    }
    token.end = s;
    *sp = s;
    return token;
}

int count_words(const char *s, char sep)
{
    int count;
    t_token token;

    count = 0;
    token = ft_get_token(&s, sep);
    while(token.top != NULL)
    {
        ++count;
        token = ft_get_token(&s, sep);
    }
    return (count);
}

char *ft_split_strsub(t_token token)
{
    size_t len;
    char *sub;

    len = token.end - token.top;
    sub = malloc(len + 1);
    if (sub)
    {
        memcpy(sub, token.top, len);
        sub[len] = 0;
    }
    return sub;
}

char **ft_strsplit(const char *s, char sep)
{
    int words;
    int i;
    char **result;
    t_token token;

    if (!s || !sep || !(words = count_words(s, sep)))
        return NULL;
    result = malloc(sizeof(char *) * (words + 1));
    if(!result)
        return NULL;
    i = 0;
    token = ft_get_token(&s, sep);

    while(token.top != NULL){
        result[i++] = ft_split_strsub(token);
        token = ft_get_token(&s, sep);
    }
    result[i] = NULL;
    return result;
}