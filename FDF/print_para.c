/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_para.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:47:37 by agesp             #+#    #+#             */
/*   Updated: 2019/01/21 18:11:36 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long	ft_map(long x, long in_min, long in_max, long out_min, long out_max)
{
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int		get_pers(int a, int b)
{
	if (a < b)
		return (b * 1);
	else if (a > b)
		return (b * -1);
	else
		return (b * 1);
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
				ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 100) - p->tab[j][i] * 1;
			line->xf = (j) * (p->zoom) + (p->x > 50 ?
				ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 100)
				- get_pers(p->tab[j][i], p->tab[j][i + 1]);
			line->yi = i * (p->zoom)
				+ (p->y > 50 ? 100 : 1) - p->tab[j][i] * 1;
			line->yf = (i + 1) * (p->zoom)
				+ (p->y > 50 ? 100 : 1) - get_pers(p->tab[j][i], p->tab[j][i + 1]);
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
					ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 100) - p->tab[i][j] * 1;
			line->xf = (i + 1) * (p->zoom) + (p->x > 50 ?
					ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 100)
				- get_pers(p->tab[i][j], p->tab[i + 1][j]);
			line->yi = j * (p->zoom) + (p->y > 50 ? 100
					: 1) - p->tab[i][j] * 1;
			line->yf = j * (p->zoom)
				+ (p->y > 50 ? 100 : 1) - get_pers(p->tab[i][j], p->tab[i + 1][j]);
			line->color = 0xFF0000 + ft_map(p->tab[i][j], p->min, p->max, 0, 65535);
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
}
