#include "ft_printf.h"

int	is_ok_flag(const char *format, int i)
{
	if (format[i] == 'd'
			|| format[i] == 'i' || format[i] == 's'
			|| format[i] == 'c' || format[i] == 'p'
			|| format[i] == 'u' || format[i] == 'o'
			|| format[i] == 'x' || format[i] == 'X'
			|| format[i] == '%')
		return (1);
	return (0);
}

int	is_ok_conv(const char *format, int *pos)
{
	int	i;

	i = *pos;
	if (format[i] == 'h' && format[i + 1] == 'h')
		i += 2;
	if (format[i] == 'h')
		i++;
	if (format[i] == 'l' && format[i + 1] == 'l')
		i += 2;
	if (format[i] == 'l')
		i++;
	if (i != *pos && is_dioux(format, i))
	{
		*pos = i;
		return (1);
	}
	return (0);
}

int	check_dot(const char *format, int i)
{
	i++;
	while (format[i] && ft_isdigit(format[i]))
		i++;
	if (!format[i] || !(is_dioux(format, i)
				|| is_ok_conv(format, &i)))
		return (0);
	return (i);
}

int	check_sign(const char *format, int i)
{
	if ((format[i] == '+' || format[i] == '-' 
				|| format[i] == ' ') && format[i + 1] 
			&& (is_dioux(format, i + 1) || format[i + 1] == '.'
				|| ft_isdigit(format[i + 1])
				|| is_ok_conv(format, &i)))
		return (1);
	return (0);
}

int	correct_flags(const char *format, int i)
{
	if (format[i] && !(is_ok_flag(format, i)))
	{
		if (check_sign(format, i))
				i++;
		if (ft_isdigit(format[i]))
		{
			while (format[i] && ft_isdigit(format[i]))
				i++;
			if (!format[i] || !(is_dioux(format, i) || format[i] == '.'
						|| is_ok_conv(format, &i)))
				return (0);
			if (format[i] == '.')
				return (correct_flags(format, i));
			return (i);
		}
		if (format[i] == '.')
			return (check_dot(format, i));
		if (is_ok_conv(format, &i))
			return (i);
	}
	if (is_ok_flag(format, i))
		return (i + 1);
	else
		return (0);
}
