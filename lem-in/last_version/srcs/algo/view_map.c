/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:37:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:37:45 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	 	draw_breseham(int yi, int xi, int yf, int xf, t_mlx *v)
{
	int dx,dy,i,xinc,yinc,cumul,x,y ;
	x = xi ;
	y = yi ;
	dx = xf - xi ;
	dy = yf - yi ;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	dx = ft_abs(dx) ;
	dy = ft_abs(dy) ;
	img_pixel_put(v, x,y);
	i = -1;
	if ( dx > dy ) 
	{
		cumul = dx / 2 ;
		while (++i < dx) 
		{
			x += xinc ;
			cumul += dy ;
			if ( cumul >= dx ) 
			{
				cumul -= dx ;
				y += yinc ; 
			}
			img_pixel_put(v, x, y) ; 
		} 
	}
	else 
	{
		i = -1;
		cumul = dy / 2 ;
		while (++i < dy) 
		{
			y += yinc ;
			cumul += dx ;
			if ( cumul >= dy ) 
			{
				cumul -= dy ;
				x += xinc ; 
			}
			img_pixel_put(v, x, y) ; 
		} 
	}
}

void 		view_coor(t_rooms *r, t_mlx *v)
{
	v->color = 0xfbc531;
	v->d = init_design(r->x, r->y, r->y + 20, r->x + 20);
	function_color(v->d, v);
}

void 		view_link(t_links *l, t_mlx *v)
{
	int y;
	int x;
	int fy;
	int fx;

	x = v->e->h[generate_hash(l->s1, v->e->nb_rooms)]->r->x;
	y = v->e->h[generate_hash(l->s1, v->e->nb_rooms)]->r->y;
	fx = v->e->h[generate_hash(l->s2, v->e->nb_rooms)]->r->x;
	fy = v->e->h[generate_hash(l->s2, v->e->nb_rooms)]->r->y;
	v->color = 0xe1b12c;
	draw_breseham(y, x, fy, fx, v);
}

void		init_coor_room_map(t_lemin *e, t_mlx *v, int  count_nb_map)
{
	t_rooms *r;
	int y;
	int x;

	r = e->r;
	x = v->wspace;
	v->hspace = 1000 / count_nb_map;
	y = v->hspace;
	while (r)
	{
		if (e->map[r->nb_rooms][r->nb_rooms] == 5)
		{
			e->map[r->nb_rooms][r->nb_rooms] = 2;
			r->y = y;
			r->y += 70;
			y += v->hspace;
			r->x = x;
		}
		r = r->next;
	}
	v->wspace += v->tmpspacew;
}

void	 space_init(t_lemin *e, t_mlx *v)
{
	int x;
	int y;
	int bool_tcheck;
	int count_nb_map;

	count_nb_map = 0;
	bool_tcheck = 0;
	y = 0;
	while (1)
	{
		while (y < e->nb_rooms)
		{
			x = 0;
			if (e->map[y][y] == 2)
			{
				e->map[y][y] = 3;
				while (x < e->nb_rooms)
				{	
					if (e->map[y][x] == 1 && e->map[x][x] != 3)
					{
						count_nb_map++;
						bool_tcheck = 1;
						e->map[x][x] = 5;
					}
					x++;
				}
			}
			y++;
		}
		if (bool_tcheck == 0)
			break ;
		else
		{
			init_coor_room_map(e, v, count_nb_map);
			count_nb_map = 0;
			y = 0;
			bool_tcheck = 0;
		}
	}
}

int 		max(t_lemin *e)
{
	t_path *p;
	int i;

	i = 0;
	p = e->p;
	while (p)
	{
		i = p->size_path;
		p = p->next;
	}
	return (i);
}

void 		move_ants(t_mlx *v)
{
	int i;
	t_ants *a;

	i = 0;
	a = v->e->a;
	a->color = a->nb_ants * 10;

}

void 		viewer(t_mlx *v)
{
	t_rooms *r;
	t_links *l;
	int y;
	int x;
	int max_path;

	max_path = max(v->e);
	max_path += 2;
	y = 0;
	x = 0;
	mlx_clear_window(v->mlx_ptr, v->win_ptr);
	r = v->e->r;
	l = v->e->l;
	v->e->start->y = HEIGHT / 2 + 10;
	v->e->start->x = WIDTH / v->e->nb_rooms;
	v->e->h[generate_hash(v->e->start->name, v->e->nb_rooms)]->r->y =  HEIGHT / 2 + 10;
	v->e->h[generate_hash(v->e->start->name, v->e->nb_rooms)]->r->x =  50;
	y = v->e->h[generate_hash(v->e->start->name, v->e->nb_rooms)]->r->nb_rooms;
	v->e->map[y][y] = 2;
	v->tmpspacew = WIDTH / max_path;
	ft_abs(v->tmpspacew);
	v->wspace = v->tmpspacew;
	space_init(v->e, v);
	while (r)
	{
		view_coor(r, v);
		r = r->next;
	}
	while (l)
	{
		view_link(l, v);
		l = l->next;
	}
	move_ants(v);
	design_windows(v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->image->img,
			0, 0);
	info(v);
}
