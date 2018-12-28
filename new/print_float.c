#include "ft_printf.h"

void	print_float(va_list *ap, t_plist *list)
{
	double	save;
	int	fpart;
	char	*part1;
	char	*part2;
	char	*ret;


	save = (double)va_arg(*ap, double);
	printf("%f\n", save);
	fpart = save;
	part1 = ft_itoa(fpart);
	list->precision = list->precision == 0 ? 6 : list->precision;
	fpart = ((float)save * ft_pow(10, list->precision))
		- (fpart * ft_pow(10, list->precision));;
	part2 = ft_itoa(fpart);
	fpart = (int)ft_strlen(part1);
	if (!(ret = malloc(sizeof(char) * (fpart
		+ (list->precision != -1 ? (int)ft_strlen(part2) + 1 : 0) + 1))))
		return ;
	ft_strcpy(ret, part1);
	if (list->precision != -1)
	{
		ret[fpart] = '.';
		ft_strcat(ret, part2);
	}
	ft_putstr(ret);
}
