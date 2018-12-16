#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct		s_plist
{
	char	flag;
	int	conversion;
	int	precision;
	int	min_width;
	char	sign;
}			t_plist;

int	correct_flags(const char *format, int i);
int	is_dioux(const char *format, int i);
int	is_sign(const char *format, int i);
int	is_csp(const char *format, int i);
int	is_convert(const char *format, int i);

#endif
