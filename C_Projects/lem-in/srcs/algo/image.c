/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:37:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/08 16:42:25 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	img_pixel_put(t_mlx *e, int x, int y)
{
	int		e_pos;

	if (x <= 0 || y <= 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	e_pos = (x * e->image->img_bpp / 8) + (y * e->image->img_size_line);
	e->image->img_data[e_pos] = e->color % 256;
	e->image->img_data[e_pos + 1] = (e->color >> 8) % 256;
	e->image->img_data[e_pos + 2] = (e->color >> 16) % 256;
}

void	clear_image(t_mlx *e)
{
	mlx_destroy_image(e->mlx_ptr, e->image->img);
	e->image->img = mlx_new_image(e->mlx_ptr, WIDTH, HEIGHT);
	e->image->img_data = mlx_get_data_addr(e->image->img, &(e->image->img_bpp),
			&(e->image->img_size_line), &(e->image->img_endian));
}
