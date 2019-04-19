/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:38:01 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 11:49:32 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	free_visu(t_mlx *v)
{
	t_lemin *e;

	e = v->e;
	mlx_destroy_image(v->mlx_ptr, v->image->img);
	mlx_destroy_window(v->mlx_ptr, v->win_ptr);
	free(v->image);
	free(v->even);
	free(v);
	lem_in_error(e, -2);
}

int		deal_hook(void *param)
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

void	malloc_struct(t_mlx *v)
{
	if (!(v->image = ft_memalloc(sizeof(t_image)))
			|| !(v->even = ft_memalloc(sizeof(t_event))))
		free_visu(v);
}

void	visu(t_lemin *e)
{
	t_mlx	*v;

	if (!(v = ft_memalloc(sizeof(t_mlx))))
		free_visu(v);
	malloc_struct(v);
	v->e = e;
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, WIDTH, HEIGHT, "lem_in");
	v->image->img = mlx_new_image(v->mlx_ptr, WIDTH, HEIGHT);
	v->image->img_data = mlx_get_data_addr(v->image->img, &(v->image->img_bpp),
			&(v->image->img_size_line), &(v->image->img_endian));
	mlx_expose_hook(v->win_ptr, deal_hook, v);
	viewer(v);
	mlx_key_hook(v->win_ptr, deal_key, v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->image->img, 0, 0);
	mlx_loop(v->mlx_ptr);
	free_visu(v);
}
