#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct		s_plist
{
	int	flag;
	int	conversion;
	int	precision;
	int	min_width;
	char	sign[4];
	int		size;
}			t_plist;


void	print_precision(t_plist *list, char *ret, int flag);
void	print_minus_wd(t_plist *list, char *ret, int plus, int len);
void	print_pw_minus(t_plist *list, char *ret);
void	integer_print(t_plist *list, va_list *ap);
void	print_float(va_list *ap, t_plist *list);
int		ft_printf(const char *format, ...);
int		correct_flags(const char *format, int i);
int		is_dioux(const char *format, int i);
int		is_sign(const char *format, int i);
int		is_csp(const char *format, int i);
int		is_convert(const char *format, int i);
void	complete_list(const char *format, int *pos, t_plist *list);
int		print_list(t_plist *list, va_list *ap);
void	w_print_char(wchar_t c);
void	w_print_str(wchar_t *s);
int		print_wp(t_plist *list, int len, char *ret);
void		print_wp_x(t_plist *list, int len, int hash);
void	print_x(t_plist *list, va_list *ap);
void	print_s(t_plist *list, va_list *ap);
void	print_u(t_plist *list, va_list *ap);
void	print_p(t_plist *list, va_list *ap);
void	print_o(t_plist *list, va_list *ap);
void	print_percent(t_plist *list);
void	print_c(t_plist *list, va_list *ap);
char	*convert_dioux(char flag, va_list *ap, int base, int conv);
void	print_width(t_plist *list, int len);

#endif
