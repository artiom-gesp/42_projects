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
	
	i = *pos;
	if (is_sign(format, i))
	{
		list->sign = format[i];
		i++;
	}
}
void	make_plist(const char *format)
{
	int	i;
	t_plist	*list;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '%')
		{
			ft_putchar('%');
			i += 2;
		}
		if (format[i] == '%' && format[i + 1] != '%')
			complete_list(format, &i, list);
	}
}

int	ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	int		i;

	i = 0;
	if (!(are_flags_correct(format)))
		return (0);
	//make_plist(format, list);
	//return (print_list(&ap));
	return (1);
}

int	main(int ac, char **av)
{
	printf("%d\n", ft_printf(av[1], 12));
}
