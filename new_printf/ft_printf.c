#include "ft_printf.h"

int	are_flags_correct(const char *format)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (format[i + 1])
	{
		if (format[i] == '%')
		{
			i++;
			if (!(flag = correct_flags(format, i)))
				return (0);
			i = flag;
		}
		else
			i++;
	}
	if (format[i] == '%')
		return (0);
	return (1);
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
	{
		while (ft_isdigit(format[i]))
			i++;
		if (!(save = ft_strnew(i - *pos)))
			return ;
		ft_strncpy(save, format + *pos, i - *pos);
		digit = ft_atoi(save);
		free(save);
		list->min_width = digit;
	}
	*pos = i;
	if (format[i] == '.')
	{
		i++;
		while (ft_isdigit(format[i]))
			i++;
		if (!(save = ft_strnew(i - *pos)))
			return ;
		ft_strncpy(save, format + *pos + 1, i - *pos);
		digit = ft_atoi(save);
		free(save);
		list->precision = digit;
	}
	if (is_convert(format, i))
	{
		list->conversion = is_convert(format,i);
		if (list->conversion == 1 || list->conversion == 3)
			i++;
		else
			i += 2;
	}
	list->flag = format[i];
	i++;
	*pos = i;
}

void	reset_list(t_plist *list)
{
	list->flag = 0;
	list->conversion = 0;
	list->precision = 0;
	list->min_width = 1;
	list->sign = 0;
}

void	make_plist(const char *format)
{
	int	i;
	t_plist	*list;

	i = 0;
	while (format[i])
	{
		reset_list(list);
		if (format[i] == '%' && format[i + 1] == '%')
		{
			ft_putchar('%');
			i += 2;
		}
		if (format[i] == '%' && format[i + 1] != '%')
		{
			i++;
			complete_list(format, &i, list);
			printf("flag %c\n", list->flag);
			printf("conv %d\n", list->conversion);
			printf("prec %d\n", list->precision);
			printf("min %d\n", list->min_width);
			printf("sign %c\n\n", list->sign);
		}
		if (i < ft_strlen(format))
			ft_putchar(format[i]);
		i++;
	}
}

int	ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	int		i;

	i = 0;
	if (!(are_flags_correct(format)))
		return (0);
	make_plist(format);
	//return (print_list(&ap));
	return (1);
}

int	main(int ac, char **av)
{
	printf("%d\n", ft_printf(av[1], 12));
}
