#include "ft_printf.h"

int	is_dioux(const char *format, int i)
{
	if (format[i] == 'd' || format[i] == 'i' || format[i] == 'u'
			|| format[i] == 'o'
			|| format[i] == 'x' || format[i] == 'X')
		return (1);
	return (0);
}

int	is_sign(const char *format, int i)
{
	if (format[i] == '+' || format[i] == '-' || format[i] == ' '
			|| format[i] == '#')
		return (1);
	return (0);
}

int	is_csp(const char *format, int i)
{
	if (format[i] == 'c' || format[i] == 's' || format[i] == 'p')
		return (1);
	return (0);
}
