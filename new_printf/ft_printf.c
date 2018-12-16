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

void	reset_list(t_plist *list)
{
	list->flag = 0;
	list->conversion = 0;
	list->precision = 0;
	list->min_width = 1;
	list->sign = 0;
}

void	make_plist(const char *format, va_list *ap)
{
	int	i;
	t_plist	*list;

	i = 0;
	list = malloc(sizeof(t_plist*));
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
			print_list(list, ap);
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
	va_start(ap, format);
	if (!(are_flags_correct(format)))
		return (0);
	make_plist(format, &ap);
	//return (print_list(&ap));
	return (1);
}

int	main(int ac, char **av)
{
	ft_printf(av[1], 1212121212);
	printf("\n");
	printf("%+-# s", 1212121212);
}
