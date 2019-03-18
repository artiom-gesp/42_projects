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
	int y;
	int x;
	int fy;
	int fx;

	y = r->y;
	x = r->x;
	ft_putnbr(v->e->maxy);
	ft_putnbr(v->e->maxx);
	if (r->next)
	{
		fy = v->space + r->next->y + 30;
		fx = v->space + r->next->x + 30;
	}
	v->color = 0xfbc531;
	*(v->d) = init_design(v->space + r->x, v->space + r->y, v->space + r->y + 20, v->space + r->x + 20);
	function_color(v->d, v);
}

void 		view_link(t_links *l, t_mlx *v)
{
	int y;
	int x;
	int fy;
	int fx;

	x = v->e->h[generate_hash(l->s1, v->e->nb_rooms)]->r->x + v->space;
	y = v->e->h[generate_hash(l->s1, v->e->nb_rooms)]->r->y + v->space;
	fx = v->e->h[generate_hash(l->s2, v->e->nb_rooms)]->r->x + v->space;
	fy = v->e->h[generate_hash(l->s2, v->e->nb_rooms)]->r->y + v->space;
	v->color = 0xe1b12c;
	draw_breseham(y, x, fy, fx, v);
}

void 		viewer(t_mlx *v)
{
	t_rooms *r;
	t_links *l;

	mlx_clear_window(v->mlx_ptr, v->win_ptr);
	v->space = 200;
	r = v->e->r;
	l = v->e->l;
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
	design_windows(v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->image->img,
	0, 0);
	info(v);
}