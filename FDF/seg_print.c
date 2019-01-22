/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 11:24:06 by agesp             #+#    #+#             */
/*   Updated: 2019/01/22 13:49:05 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init(t_line *line, t_fstruct *p)
{
	line->x = line->xi;
	line->y = line->yi;
	line->dx = line->xf - line->xi;
	line->dy = line->yf - line->yi;
	line->xplus = (line->dx > 0) ? 1 : -1;
	line->yplus = (line->dy > 0) ? 1 : -1;
	line->dx *= line->dx < 0 ? -1 : 1;
	line->dy *= line->dy < 0 ? -1 : 1;
	mlx_pixel_put(p->init, p->win, line->x, line->y, line->color);
}

static void	print_ft(t_line *line, t_fstruct *p)
{
	int i;

	line->both = line->dx / 2;
	i = 1;
	while (i <= line->dx)
	{
		line->x += line->xplus;
		line->both += line->dy;
		if (line->both >= line->dx)
		{
			line->both -= line->dx;
			line->y += line->yplus;
		}
		mlx_pixel_put(p->init, p->win, line->x, line->y, line->color);
		i++;
	}
}

void		print_seg(t_line *line, t_fstruct *p)
{
	int i;

	i = 0;
	init(line, p);
	if (line->dx > line->dy)
		print_ft(line, p);
	else
	{
		line->both = line->dy / 2;
		i = 1;
		while (i <= line->dy)
		{
			line->y += line->yplus;
			line->both += line->dx;
			if (line->both >= line->dy)
			{
				line->both -= line->dy;
				line->x += line->xplus;
			}
			mlx_pixel_put(p->init, p->win, line->x, line->y, line->color);
			i++;
		}
	}
}
