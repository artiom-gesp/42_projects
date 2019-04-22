/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:37:05 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:51:25 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include "lib.h"
# include <wchar.h>
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define CYAN		"\033[36m"
# define EOC		"\033[37m"
# define PRINTFBUFFER 400

typedef struct	s_parsing
{
	int			decimal;
	int			attr;
	int			hash;
	int			min;
	int			max;
	int			space;
	int			zero;
	int			cotes;
	int			wild;
	int			prec;
	int			mod_long;
	int			h;
	int			hh;
	int			l;
	int			ll;
	int			j;
	int			z;
	char		conv;
	char		car;
}				t_parsing;

int				ft_atoi_adv(const char **tmp_stack);
int				is_special_prec(t_parsing *lst, char *str);
int				ft_printf(const char *format, ...);
const char		*glob_init(va_list arg, const char *format, \
				int *ret, t_parsing *lst);
t_parsing		*init_prec(t_parsing *lst, const char **stack);
int				initialiser_mod_long(t_parsing **lst,\
				const char **stack);
int				init_conv(const char **format, t_parsing **lst);
t_parsing		*init_lst(t_parsing *lst);
int				init_attr(t_parsing **lst, const char *stack);
void			parsing_conv(va_list arg, t_parsing *lst,\
				int *ret);
void			conv_double(va_list arg, t_parsing *lst,\
				int *ret);
void			conv_string(va_list arg, t_parsing *lst,\
				int *ret);
void			conv_wstr(va_list arg, t_parsing *lst, int *ret);
void			conv_void_p(va_list arg, t_parsing *lst, int *ret);
void			conv_int_p(va_list arg, t_parsing *lst, int *ret);
void			conv_decimal(va_list arg, t_parsing *lst, int *ret);
void			conv_udecimal(va_list arg, t_parsing *lst, int *ret);
char			*controller_attr(t_parsing *lst, char *dec);
uintmax_t		controller_spec_mod_unsinged(t_parsing *lst, va_list arg,\
				uintmax_t dec);
intmax_t		controller_spec_mod(t_parsing *lst, va_list arg,\
				intmax_t dec);
char			*controller_decimal(t_parsing *lst, char *str);
char			*controller_prec(t_parsing *lst, char *str);
wchar_t			*applywidthwchar(t_parsing *lst, wchar_t *wstr);
wchar_t			*applyprecisionwchar(t_parsing *lst, wchar_t *wstr);
wchar_t			*wstraddnchar(wchar_t *wstr, int check, int n, char c);
char			*addoctachar(char *str);
char			*addhexachar(char *str, int ishexa, char *s1);
char			*straddncharsigned(char *str, int n, char c);
char			*straddnchar(char *str, int check, int n, char c);
void			freestr(char *str);
void			freewstr(wchar_t *wstr);
int				putlstwstr(t_parsing *lst, wchar_t *wstr);
void			strprint(char *format, int *ret);
const char		*ft_print(const char *format, int *ret);
char			*ft_itoa_base(intmax_t value, int base, t_parsing *lst);
char			*ft_uitoa_base(uintmax_t value, int base,\
				t_parsing *lst);
int				ishexa(t_parsing *lst);
int				isocta(t_parsing *lst);
int				is_digit(int c);
int				issigned(t_parsing *lst);
int				isunsigned(t_parsing *lst);

typedef struct	s_conv
{
	char		check;
	void		(*f)(va_list, t_parsing *, int *);
}				t_conv;

#endif
