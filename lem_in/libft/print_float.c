/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 10:46:24 by agesp             #+#    #+#             */
/*   Updated: 2019/01/08 15:46:48 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	zero_p(char **ret, t_plist *list)
{
	(void)list;
	if (!ft_strcmp(*ret, "0") && list->precision == -1)
	{
		free(*ret);
		*ret = "";
	}
}

char	*round_float(double save, int precision, long long fpart)
{
	uintmax_t	spart;
	char		*ret;
	int			len;

	spart = (save * ft_pow(10, precision + 1))
		- (fpart * ft_pow(10, precision + 1));
	spart *= fpart < 0 ? -1 : 1;
	ret = ft_itoa_base(spart, 10, 'a');
	len = (int)ft_strlen(ret);
	if (ret[len - 1] >= '5')
	{
		ret[len - 2] += 1;
		ret[len - 1] = '\0';
	}
	else
		ret[len - 1] = '\0';
	return (ret);
}

void	print_wp_float(t_plist *list, char *ret)
{
	int		minus;

	minus = ft_strchr(list->sign, '-') ? 1 : 0;
	list->precision = 0;
	if (!ft_strcmp(ret, "0") && list->precision == -1)
	{
		if (list->min_width == 0)
			return ;
		ret = "";
	}
	if (list->precision >= list->min_width)
		print_precision(list, ret, 1);
	else if (list->precision < list->min_width && minus)
		print_pw_minus(list, ret);
	else if (list->precision < list->min_width)
	{
		if (print_wp(list, (int)ft_strlen(ret), ret))
		{
			ret++;
		}
		ft_putstr(ret);
		list->size += (int)ft_strlen(ret);
	}
}

void	print_float(va_list *ap, t_plist *list)
{
	double		save;
	long long	fpart;
	char		*part1;
	char		*part2;
	char		*ret;

	save = (double)va_arg(*ap, double);
	fpart = save;
	part1 = ft_itoa_base(fpart, 10, 'a');
	list->precision = list->precision == 0 ? 6 : list->precision;
	part2 = round_float(save, list->precision, fpart);
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
	print_wp_float(list, ret);
}
