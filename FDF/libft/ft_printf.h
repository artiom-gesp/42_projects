/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 12:20:10 by agesp             #+#    #+#             */
/*   Updated: 2019/01/09 15:14:23 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct		s_plist
{
	int		flag;
	int		conversion;
	int		precision;
	int		min_width;
	char	sign[4];
	int		size;
}					t_plist;

void				print_precision(t_plist *list, char *ret, int flag);
void				zero_p(char **ret, t_plist *list);
void				complete_start_sign(const char *format, int *pos);
int					print_zero(int lim);
void				print_minus_wd(t_plist *list, char *ret, int plus, int len);
void				print_pw_minus(t_plist *list, char *ret);
void				integer_print(t_plist *list, va_list *ap);
void				print_float(va_list *ap, t_plist *list);
int					ft_printf(const char *format, ...);
int					correct_flags(const char *format, int i);
void				remove_flag(t_plist *list);
void				sort_flags(t_plist *list, char flag);
int					is_dioux(const char *format, int i);
int					is_sign(const char *format, int i);
int					is_csp(const char *format, int i);
int					is_convert(const char *format, int i);
void				complete_list(const char *format, int *pos,
		t_plist *list, va_list *ap);
int					print_list(t_plist *list, va_list *ap);
void				w_print_char(wchar_t c);
void				w_print_str(wchar_t *s);
void				print_hash(t_plist *list, char *ret);
void				is_minus(char **ret, int *len, t_plist *list);
int					print_wp(t_plist *list, int len, char *ret);
void				print_wp_x(t_plist *list, int len, int hash);
void				print_x(t_plist *list, va_list *ap);
void				print_s(t_plist *list, va_list *ap);
void				do_nothing(void);
int					is_int(char c);
void				print_u(t_plist *list, va_list *ap);
void				print_p(t_plist *list, va_list *ap);
void				print_o(t_plist *list, va_list *ap);
void				print_percent(t_plist *list);
void				print_c(t_plist *list, va_list *ap);
char				*convert_dioux(char flag, va_list *ap, int base, int conv);
void				print_width(t_plist *list, int len);
void				print_sign(t_plist *list, char *ret, int flag);
int					zero_ret(char **ret, t_plist *list, int *hash);
void				complete_stars(va_list *ap, const char *format,
		int pos, t_plist *list);

#endif
