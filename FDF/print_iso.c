/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_iso.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:28:58 by agesp             #+#    #+#             */
/*   Updated: 2019/01/22 16:32:58 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	center(int i, int j, int zoom)
{
	return ((j - i) * zoom < 0 ? (j - i) * -zoom : 50);
}

static void	print_fp(t_fstruct *p, t_line *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	center(i,i,i);
	while (i < p->y)
	{
		j = 0;
		while (j < p->x - 1)
		{
			line->xi = (j - i) * (p->zoom) + p->y * p->zoom;
			line->xf = (j - i + 1) * (p->zoom) + p->y * p->zoom;
			line->yi = (j + i) * (p->zoom / 2)
				+ (p->y > 50 ? 100 : p->y) - p->tab[j][i] * p->contrast + p->contrast * 10;
			line->yf = (j + i + 1) * (p->zoom / 2)
				+ (p->y > 50 ? 100 : p->y) - p->tab[j + 1][i] * p->contrast + p->contrast * 10;
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
			line->xi = (i - j) * (p->zoom) + p->y * p->zoom;
			line->xf = (i - (j + 1)) * (p->zoom) + p->y * p->zoom;
			line->yi = (j + i) * (p->zoom / 2) + (p->y > 50 ? 100
					: p->y) - p->tab[i][j] * p->contrast + p->contrast * 10;
			line->yf = (j + i + 1) * (p->zoom / 2)
				+ (p->y > 50 ? 100 : p->y) - p->tab[i][j + 1] * p->contrast + p->contrast * 10;
			line->color = 0xFF0000 + ft_map(p->tab[i][j], p->min, p->max, 0, 65535);
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
}
