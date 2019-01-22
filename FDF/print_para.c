/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_para.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:47:37 by agesp             #+#    #+#             */
/*   Updated: 2019/01/22 17:16:34 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long	ft_map(long x, long in_min, long in_max, long out_min, long out_max)
{
	if (in_max == in_min)
		return (0);
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int		get_pers(int a, int b, int o)
{
//	b *= b < 0 && !flag ? -1 : 1;
	if (o > 60)
	{
		if (a < b)
			return (b / 7);
		else if (a > b)
			return (b / -7);
		else
			return (b / 7);
	}
	if (a < b)
		return (a * 1);
	else if (a > b && b > 0)
		return (-b * 10);	
	else
		return (b * 10);

}

static void	print_fp(t_fstruct *p, t_line *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < p->y - 1)
	{
		j = 0;
		while (j < p->x)
		{
			line->xi = j * (p->zoom) + (p->x > 50 ?
				ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 100) - (p->x < 60 ? p->tab[j][i] * 10 : p->tab[j][i] / 7);
			line->xf = j * (p->zoom) + (p->x > 50 ?
				ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 100)
				- get_pers(p->tab[j][i], p->tab[j][i + 1], p->x);
			line->yi = i * (p->zoom)
				+ (p->y > 50 ? 100 : 100) - (p->x < 60 ? p->tab[j][i] * 10 : p->tab[j][i] / 7);
			line->yf = (i + 1) * (p->zoom)
				+ (p->y > 50 ? 100 : 100) - get_pers(p->tab[j][i], p->tab[j][i + 1], p->x);
			line->color = 0xFF0000 + ft_map(p->tab[j][i], p->min, p->max, 0, 65535);
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
}

void		print_para(t_fstruct *p, t_line *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	print_fp(p, line);
	while (i < p->x - 1)
	{
		j = 0;
		while (j < p->y)
		{
			line->xi = i * (p->zoom) + (p->x > 50 ?
					ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 100) - (p->x < 60 ? p->tab[i][j] * 10: p->tab[i][j] / 7);
			line->xf = (i + 1) * (p->zoom) + (p->x > 50 ?
					ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 100)
				- get_pers(p->tab[i][j], p->tab[i + 1][j], p->x);
			line->yi = j * (p->zoom) + (p->y > 50 ? 100
					: 100) - (p->x < 60 ? p->tab[i][j] * 10: p->tab[i][j] / 7);
			line->yf = j * (p->zoom)
				+ (p->y > 50 ? 100 : 100) - get_pers(p->tab[i][j], p->tab[i + 1][j], p->x);
			line->color = 0xFF0000 + ft_map(p->tab[i][j], p->min, p->max, 0, 65535);
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
}
