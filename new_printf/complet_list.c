#include "ft_printf.h"

void	complete_dot(const char *format, int *pos, t_plist *list)
{
	int	i;
	char	*save;
	int	digit;

	i = *pos;
	i++;
	while (ft_isdigit(format[i]))
		i++;
	if (!(save = ft_strnew(i - *pos)))
		return ;
	ft_strncpy(save, format + *pos + 1, i - *pos);
	digit = ft_atoi(save);
	free(save);
	list->precision = digit;
	*pos = i;
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

void	complete_list(const char *format, int *pos, t_plist *list)
{
	int	i;
	char	*save;
	int	digit;

	i = *pos;
	if (is_sign(format, i))
	{
		list->sign = format[i];
		i++;
	}
	*pos = i;
	if (ft_isdigit(format[i]))
		complete_width(format, &i, list);
	*pos = i;
	if (format[i] == '.')
		complete_dot(format, &i, list);
	if (is_convert(format, i))
		complete_convert(format, &i, list);
	list->flag = format[i];
	i++;
	*pos = i;
}
