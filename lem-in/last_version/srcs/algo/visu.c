/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:38:01 by kecosmon          #+#    #+#             */
/*   Updated: 2019/03/18 10:59:23 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int			deal_hook(void *param)
{
	t_mlx *v;

	v = (t_mlx *)param;
	mlx_clear_window(v->mlx_ptr, v->win_ptr);
	design_windows(v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->image->img,
	0, 0);
	info(v);
	return (1);
}

void		malloc_struct(t_mlx *v)
{
	if (!(v->image = malloc(sizeof(t_image))) &&
		!(v->even = malloc(sizeof(t_event))))
		exit(-1);
}

void		visu(t_lemin *e)
{
	t_mlx	*v;

	v = malloc(sizeof(t_mlx));
	v->e = e;
	malloc_struct(v);

	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, WIDTH, HEIGHT, "lem_in");
	v->image->img = mlx_new_image(v->mlx_ptr, WIDTH, HEIGHT);
	v->image->img_data = mlx_get_data_addr(v->image->img, &(v->image->img_bpp),\
	&(v->image->img_size_line), &(v->image->img_endian));
	viewer(v);
	mlx_key_hook(v->win_ptr, deal_key, v);
	mlx_expose_hook(v->win_ptr, deal_hook, v);
	mlx_loop(v->mlx_ptr);
}
