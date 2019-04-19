/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:37:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 11:49:19 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void			draw_bresehamb(t_mlx *v, t_design *d, t_point p)
{
	int cumul;
	int i;

	img_pixel_put(v, d->x, d->y);
	i = -1;
	cumul = p.dy / 2;
	while (++i < p.dy)
	{
		d->y += p.yinc;
		cumul += p.dx;
		if (cumul >= p.dy)
		{
			cumul -= p.dy;
			d->x += p.xinc;
		}
		img_pixel_put(v, d->x, d->y);
	}
}

void			draw_breseham(t_mlx *v, t_design *d, t_point p)
{
	int cumul;
	int i;

	img_pixel_put(v, d->x, d->y);
	i = -1;
	cumul = p.dx / 2;
	while (++i < p.dx)
	{
		d->x += p.xinc;
		cumul += p.dy;
		if (cumul >= p.dx)
		{
			cumul -= p.dx;
			d->y += p.yinc;
		}
		img_pixel_put(v, d->x, d->y);
	}
}

static void		do_print(t_mlx *v, t_lemin *e, t_ants *a)
{
	if (a->p->i < a->p->size_path
			&& e->table_r[a->p->path[a->p->i]]->occuped != 2)
	{
		if (a->p->i + 1 == a->p->size_path)
			e->table_r[a->p->path[a->p->i]]->occuped = 0;
		else
			e->table_r[a->p->path[a->p->i]]->occuped = 2;
		v->color = (a->nb_ants % 2) ? a->nb_ants * 10 : a->nb_ants * 20;
		v->color += (a->nb_ants * 10) * 1000 * 255;
		v->d = init_design(e->table_r[a->p->path[a->p->i]]->x + 10,\
		e->table_r[a->p->path[a->p->i]]->y + 10,\
		e->table_r[a->p->path[a->p->i]]->y + 20,\
		e->table_r[a->p->path[a->p->i]]->x + 20);
		function_color(v->d, v);
		if (e->n != e->stop)
			ft_printf("L%d-%s ", a->nb_ants,\
			e->table_r[a->p->path[a->p->i]]->name);
		a->p->ok = 1;
	}
	else
		a->p->ok = 0;
}

static void		ants_forward(t_mlx *v, t_lemin *e, t_ants *a)
{
	while (a)
	{
		do_print(v, e, a);
		if (a->next == NULL && not_all_printed(e->a))
		{
			if (e->n != e->stop)
				ft_putchar('\n');
			zero_vistid(e);
			e->stop = e->n;
			break ;
		}
		else
			a = a->next;
	}
}

void			viewer(t_mlx *v)
{
	t_path	*p;
	t_rooms	*r;
	int		i;
	int		spacew;

	i = 1;
	r = v->e->r;
	p = v->e->p;
	spacew = init_start(v, 0);
	while (p)
	{
		init_r(v, p->size_path, p->path, v->hspace);
		if (i % 2 != 0)
			v->hspace += ((v->tmpspace * i) - 200);
		else
			v->hspace -= ((v->tmpspace * i) + 200);
		p = p->next;
	}
	rooms_links(v, v->e->r, i, spacew);
	ants_forward(v, v->e, v->e->a);
	mlx_clear_window(v->mlx_ptr, v->win_ptr);
	design_windows(v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->image->img, 0, 0);
	info(v);
}
