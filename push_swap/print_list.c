/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:04:38 by agesp             #+#    #+#             */
/*   Updated: 2019/01/30 16:54:29 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

long		ft_map(long x, t_libx *p, long out_min, long out_max)
{
	return (x) * (out_max - out_min) / (get_list_len(p->a)) + out_min;
}

static void	fill_b(t_libx *p, int *j)
{
	int i;

	i = 0;
	if (!p->b->is_data)
		while (i++ < 500)
		{
			*j += 1;
		}
	else if (p->b->is_data)
	{
		while (i < ft_map(p->b->data < 0 ? p->b->data * -1
					: p->b->data, p, 0, 500))
		{
			p->image[*j] = p->b->data < 0 ? 0x168600 : 0x1AFF00;
			p->image[*j] = p->b->color ? 0xFF0000 : p->image[*j];
			*j += 1;
			i++;
		}
		p->b->color = 0;
		while (i++ < 500)
		{
			*j += 1;
		}
	}
}

static void	fill_a(t_libx *p, int *j)
{
	int i;

	i = 0;
	if (!p->a->is_data)
		while (i < 500)
		{
			*j += 1;
			i++;
		}
	else if (p->a->is_data)
	{
		while (i < ft_map(p->a->data < 0 ? p->a->data
					* -1 : p->a->data, p, 0, 500))
		{
			p->image[*j] = p->a->data < 0 ? 0x168600 : 0x1AFF00;
			p->image[*j] = p->a->color ? 0xFF0000 : p->image[*j];
			*j += 1;
			i++;
		}
		p->a->color = 0;
		while (i++ < 500)
			*j += 1;
	}
}

static void	fill_image(t_libx *p)
{
	int i;
	int j;

	j = 0;
	i = 0;
	p->a = get_start_list(p->a);
	p->b = get_start_list(p->b);
	while (p->a)
	{
		i = 0;
		fill_a(p, &j);
		while (i < 30)
		{
			p->image[j] = 0x000000;
			j++;
			i++;
		}
		fill_b(p, &j);
		i = 0;
		if (!p->a->next)
			break ;
		p->a = p->a->next;
		p->b = p->b->next;
	}
}

void		print_plist(t_libx *p)
{
	p->a = get_start_list(p->a);
	p->b = get_start_list(p->b);
	p->pic = mlx_new_image(p->init, 1030, get_list_len(p->a));
	p->image = (int*)mlx_get_data_addr(p->pic, &p->bpp, &p->s_l, &p->endian);
	fill_image(p);
	mlx_put_image_to_window(p->init, p->win, p->pic, 20, 20);
	mlx_destroy_image(p->init, p->pic);
}
