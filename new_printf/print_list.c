#include "ft_printf.h"

char	*convert_dioux(char flag, va_list *ap, int base, int conv)
{
	char *ret;

	if (conv == 1)
		ret = ft_itoa_base(va_arg(*ap, long long), base, flag - 23);
	else if (conv == 2)
		ret = ft_itoa_base(va_arg(*ap, long), base, flag - 23);
	else if (conv == 3)
		ret = ft_itoa_base((short int)va_arg(*ap, int), base, flag - 23);
	else if (conv == 4)
		ret = ft_itoa_base(va_arg(*ap, int), base, flag - 23);
	else
		ret = ft_itoa_base(va_arg(*ap, int), base, flag - 23);
	return (ret);
}


void	print_int(t_plist *list, va_list *ap)
{
	char	*ret;
	int	i;
	int	lim;

	i = -1;
	ret = convert_dioux(list->flag, ap, 10, list->conversion);	
	lim = list->min_width > list->precision ?
		(list->min_width - ft_strlen(ret)) : list->min_width - ft_strlen(ret) - list->precision;
	if (lim > 0)
		while (++i < lim)
			list->sign == '0' ? ft_putchar('0') : ft_putchar(' ');
	if (ret[0] == '-')
	{
		ft_putchar('-');
		ret++;
	}
	i = -1;
	lim = list->precision - ft_strlen(ret);
	if (lim > 0)
		while (++i < list->precision - ft_strlen(ret))
			ft_putchar('0');
	ft_putstr(ret);
}

void	print_list(t_plist *list, va_list *ap)
{
	if (list->flag == 'd' || list->flag == 'i')
		print_int(list, ap);
}
