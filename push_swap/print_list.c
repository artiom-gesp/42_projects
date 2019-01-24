/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:04:38 by agesp             #+#    #+#             */
/*   Updated: 2019/01/24 15:22:36 by agesp            ###   ########.fr       */
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
		while (i < 500)
		{
			p->image[*j] = 0x000000;
			*j += 1;
			i++;
		}
	else if (p->b->is_data)
	{
		while (i < ft_map(p->b->data, p, 0, 500))
		{
			p->image[*j] = 0x1AFF00;
			*j += 1;
			i++;
		}
		while (i < 500)
		{
			p->image[*j] = 0x000000;
			*j += 1;
			i++;
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
			p->image[*j] = 0x000000;
			*j += 1;
			i++;
		}
	else if (p->a->is_data)
	{
		while (i < ft_map(p->a->data, p, 0, 500))
		{
			p->image[*j] = 0x1AFF00;
			*j += 1;
			i++;
		}

		while (i < 500)
		{
			p->image[*j] = 0x000000;
			*j += 1;
			i++;
		}
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
	while (p->a->next)
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
		p->a = p->a->next;
		p->b = p->b->next;
	}
}

void	print_plist(t_libx *p)
{
	p->a = get_start_list(p->a);
	p->b = get_start_list(p->b);
	p->pic = mlx_new_image(p->init, 1030, get_list_len(p->a));
	p->image = (int*)mlx_get_data_addr(p->pic, &p->bpp, &p->s_l, &p->endian);
	fill_image(p);
	mlx_put_image_to_window(p->init, p->win, p->pic, 100, 100);
	mlx_destroy_image(p->init, p->pic);
}

int		len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
