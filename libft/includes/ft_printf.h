/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 17:25:39 by julekgwa          #+#    #+#             */
/*   Updated: 2016/06/06 10:33:18 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"

typedef unsigned int	t_u_int;

char		*ft_check_flags(char *dest, char *traverse);
int			ft_printf(char *format, ...);
int			ft_str_contains(char c);
int			ft_handle_d_i(char *flags, char type, int d_i);
int			ft_flags(char flag, char *search);
void		ft_handle_o_x(char *flags, char type, char *o_x);
void		ft_pads_zeros(char *flags, int num_digits);
void		ft_strhex_lower(char *str);
char		*ft_base(unsigned long num, int base);
void		ft_strhex(char *str);
void		ft_putwchar_t(wchar_t *s);
void		ft_handle_prec(char *flags, int digits);
void		ft_manage_width(int width);
void		ft_handle_s(char *flags, char *s);
void		ft_putnstr(char const *s, int len);
int			ft_find_width(char *flags);
int			ft_manage_c(char *flags, char c);
unsigned	ft_num_digits(const int n);
int			ft_neg_to_pos(int a);
#endif
