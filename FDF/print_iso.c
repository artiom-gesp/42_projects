/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_iso.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:28:58 by agesp             #+#    #+#             */
/*   Updated: 2019/01/22 09:16:00 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_fp(t_fstruct *p, t_line *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < p->y)
	{
		j = 0;
		while (j < p->x - 1)
		{
			line->xi = (j - i) * (p->zoom) + (p->x > 50 ?
				ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 150);
			line->xf = (j - i + 1) * (p->zoom) + (p->x > 50 ?
				ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 150);
			line->yi = (j + i) * (p->zoom / 2)
				+ (p->y > 50 ? 100 : 20) - p->tab[j][i];
			line->yf = (j + i + 1) * (p->zoom / 2)
				+ (p->y > 50 ? 100 : 20) - p->tab[j + 1][i];
			line->color = 0xFF0000 + ft_map(p->tab[j][i], p->min, p->max, 0, 65535);
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
}

void		print_iso(t_fstruct *p, t_line *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	print_fp(p, line);
	while (i < p->x)
	{
		j = 0;
		while (j < p->y - 1)
		{
			line->xi = (i - j) * (p->zoom) + (p->x > 50 ?
					ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 150);
			line->xf = (i - (j + 1)) * (p->zoom) + (p->x > 50 ?
					ft_sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 150);
			line->yi = (j + i) * (p->zoom / 2) + (p->y > 50 ? 100
					: 20) - p->tab[i][j];
			line->yf = (j + i + 1) * (p->zoom / 2)
				+ (p->y > 50 ? 100 : 20) - p->tab[i][j + 1];
			line->color = 0xFF0000 + ft_map(p->tab[i][j], p->min, p->max, 0, 65535);
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
}
