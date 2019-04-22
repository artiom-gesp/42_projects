/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_para.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:47:37 by agesp             #+#    #+#             */
/*   Updated: 2019/01/23 11:05:26 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long		ft_map(long x, t_fstruct *p, long out_min, long out_max)
{
	if (p->max == p->min)
		return (0);
	return (x - p->min) * (out_max - out_min) / (p->max - p->min) + out_min;
}

static int	gc(int a, int contr)
{
	if (contr >= 0)
		return (a * contr);
	else
		return (a / -contr);
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
			line->xi = (j + gc(p->tab[j][i], p->contrast)) * (p->zoom) + 150;
			line->xf = (j + gc(p->tab[j][i + 1], p->contrast)) * (p->zoom)
				+ 150;
			line->yi = (i + gc(p->tab[j][i], p->contrast)) * (p->zoom) + 150;
			line->yf = (i + 1 + gc(p->tab[j][i + 1], p->contrast))
				* (p->zoom) + 150;
			line->color = 0xFF0000 + ft_map(p->tab[j][i], p, 0, 65535);
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
			line->xi = (i + gc(p->tab[i][j], p->contrast)) * (p->zoom) + 150;
			line->xf = (i + 1 + gc(p->tab[i + 1][j], p->contrast))
				* (p->zoom) + 150;
			line->yi = (j + gc(p->tab[i][j], p->contrast)) * (p->zoom) + 150;
			line->yf = (j + gc(p->tab[i + 1][j], p->contrast)) * (p->zoom)
				+ 150;
			line->color = 0xFF0000 + ft_map(p->tab[i][j], p, 0, 65535);
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
}
