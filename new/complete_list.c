#include "ft_printf.h"

int	complete_dot(const char *format, int *pos, t_plist *list)
{
	int	i;
	char	*save;
	int	digit;

	i = *pos;
	i++;
	while (ft_isdigit(format[i]))
		i++;
	if (!(save = ft_strnew(i - *pos)))
		return (0);
	ft_strncpy(save, format + *pos + 1, i - *pos);
	digit = ft_atoi(save);
	free(save);
	if (digit == 0)
		list->precision = -1;
	else
		list->precision = digit;
	*pos = i;
	if (digit != 0 && list->precision == -1)
		return (1);
	return (0);
}

void	complete_width(const char *format, int *pos, t_plist *list)
{
	int	i;
	char	*save;
	int	digit;

	i = *pos;
	while (ft_isdigit(format[i]))
		i++;
	if (!(save = ft_strnew(i - *pos)))
		return ;
	ft_strncpy(save, format + *pos, i - *pos);
	digit = ft_atoi(save);
	free(save);
	list->min_width = digit;
	*pos = i;
}

void	complete_convert(const char *format, int *pos, t_plist *list)
{
	int i;

	i = *pos;
	list->conversion = is_convert(format,i);
	if (list->conversion == 1 || list->conversion == 3)
		i++;
	else
		i += 2;
	*pos = i;
}

void	complete_sign(const char *format, int *pos, t_plist *list)
{
	int		i;
	int		j;

	i = *pos;
	j = 0;
	while (is_sign(format, i) && j < 4)
	{
		if (format[i] != '0' || (format[i] == '0' && format[i + 1] != '.'))
			list->sign[j] = format[i];
		if (format[i] == format[i + 1] && format[i] != '0')
			while (format[i] == format[i + 1])
				i++;
		if (format[i] == '0' && format[i + 1] == '.')
				break ;
		else
		{
			i++;
			j++;
		}
	}
		*pos = i;
}

void	remove_flag(t_plist *list)
{
	int		i;

	i = 0;
	if (ft_strchr(list->sign, '-') && ft_strchr(list->sign, '0'))
	{
		while (i < 4)
		{
			if (list->sign[i] == '0')
				list->sign[i] = 'z';
			i++;
		}
	}
}

void	complete_list(const char *format, int *pos, t_plist *list)
{
	int	i;
	int	save;

	i = *pos;
	save = 1;
	if (is_sign(format, i))
		complete_sign(format, &i, list);
	remove_flag(list);
	*pos = i;
	if (ft_isdigit(format[i]))
		complete_width(format, &i, list);
	*pos = i;
	if (format[i] == '.')
		save = complete_dot(format, &i, list);
	if (is_convert(format, i))
		complete_convert(format, &i, list);
	list->flag = format[i];
	if (save && list->flag != 's')
		list->precision = 0;
	i++;
	*pos = i;
}
