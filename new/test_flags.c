#include "ft_printf.h"

int	is_ok_flag(const char *format, int i)
{
	if (format[i] == 'd'
			|| format[i] == 'i' || format[i] == 's'
			|| format[i] == 'c' || format[i] == 'p'
			|| format[i] == 'u' || format[i] == 'o'
			|| format[i] == 'x' || format[i] == 'X'
			|| format[i] == '%' || format[i] == 'D'
			|| format[i] == 'C' || format[i] == 'S'
			|| format[i] == 'U' || format[i] == 'O'
			|| format[i] == 'f')
		return (1);
	return (0);
}

int	is_ok_conv(const char *format, int *pos)
{
	int	i;

	i = *pos;
	if (format[i] == 'h' && format[i + 1] == 'h')
		i += 2;
	else if (format[i] == 'h')
		i++;
	else if (format[i] == 'l' && format[i + 1] == 'l')
		i += 2;
	else if (format[i] == 'l')
		i++;
	if (i != *pos && (is_dioux(format, i) || format[i] == 'f'))
	{
		*pos = i;
		return (1);
	}
	return (0);
}

int	check_dot(const char *format, int i)
{
	int	j;

	i++;
	j = i;
	if (!ft_isdigit(format[i]) && !is_ok_flag(format, i) && !is_ok_conv(format, &j))
		return (0);
	while (format[i] && ft_isdigit(format[i]))
		i++;
	if (!format[i] || !(is_ok_flag(format, i)
				|| is_ok_conv(format, &i)))
		return (0);
	return (i);
}

int	check_sign(const char *format, int i)
{
	if ((format[i] == '+' || format[i] == '-'
				|| format[i] == ' ' || format[i] == '0'
				|| format[i] == '#') 
			&& format[i + 1]
			&& (is_ok_flag(format, i + 1) || format[i + 1] == '.'
				|| ft_isdigit(format[++i])
				|| is_ok_conv(format, &i) || check_sign(format, i)))
		return (1);
	return (0);
}

int	correct_flags(const char *format, int i)
{
	if (format[i] && !(is_ok_flag(format, i)))
	{
		while (check_sign(format, i))
				i++;
		if (ft_isdigit(format[i]))
		{
			while (format[i] && ft_isdigit(format[i]))
				i++;
			if (!format[i] || !(is_ok_flag(format, i) || format[i] == '.'
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
