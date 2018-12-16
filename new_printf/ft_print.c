#include "ft_printf.h"

int	correct_flags(const char *format, int *pos)
{
	int i;

	i = *pos;
	if (format[i + 1] == '%' || format[i] == 'd'
				|| format[i] == 'i' || format[i] == 's'
				|| format[i] == 'c' || format[i] == 'p'
				|| format[i] == 'u' || format[i] == 'o'
				|| format[i] == 'x' || format[i] == 'X')
	{
		*pos++;
		return (1);
	}
	if (format[i] == 'l' || format[i] == 'h'
				|| format[i] == '+' || format[i] == '-'
				|| format[i] == '#' || format[i] == '.'
				|| format[i] == ' ')
		return (2);
	return (0);
}

int	are_flags_correct(const char *format)
{
	int	i;

	i = 0;
	while (format[i + 1])
	{
		if (format[i++] == '%')
			if (!(correct_flags(format, (&i))))
				return (0);
	}
}

int	ft_printft(const char *restrict format, ...)
{
	va_list		ap;
	int		i;
	t_plist		*list;

	i = 0;
	if (!(are_flags_correct(format)))
		return (0);
	make_plist(format, list);
	return (print_list(&ap));
}

