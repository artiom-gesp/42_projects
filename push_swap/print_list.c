/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:04:38 by agesp             #+#    #+#             */
/*   Updated: 2019/01/23 18:09:24 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	my_sleep(int len)
{
	int i;

	i = 0;
	while (len)
	{
		while (i < 10000)
		{
			free(malloc(1));
			i++;
		}
		len--;
	}
}

void	print_line(int len, int flag)
{
	int i;

	i = 0;
	if (i == len)
		return ;
	while (i < len)
	{
		flag ? ft_printf("-") : ft_printf("#");
		i++;
	}
	flag ? do_nothing() : ft_printf("\n");
}

int		get_pos(t_push *a, int data)
{
	int i;
	t_push *c;

	i = 0;
	if (!(c = copy_pile(a, 1)))
		return (0);
	c = get_top_list(c);
	while (c->data != data)
	{
		rotate(c, 0, 0);
	}
		rotate(c, 0, 0);
	while (c->data != data)
	{
		if (c->data < data)
			i++;
		rotate(c, 0, 0);
	}
	free(c);
	return (i + 1);
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
		if (!p->a->is_data)
			while (i < get_list_len(p->a))
			{
				p->image[j] = 0x000000;
				j++;
				i++;
			}
		else if (p->a->is_data)
		{
			while (i < (get_list_len(p->a) - p->a->data)) 
			{
				p->image[j] = 0x000000;
				j++;
				i++;
			}
			while (i < get_list_len(p->a))
			{
				p->image[j] = 0x1AFF00;
				j++;
				i++;
			}
		}
		i = 0;
		while (i < 30)
		{
			p->image[j] = 0x000000;
			j++;
			i++;
		}
		i = 0;
		if (!p->b->is_data)
			while (i < get_list_len(p->a))
			{
				p->image[j] = 0x000000;
				j++;
				i++;
			}
		else if (p->a->is_data)
		{
			while (i < get_list_len(p->a) - p->b->data)
			{
				p->image[j] = 0x000000;
				j++;
				i++;
			}
			while (i < get_list_len(p->a))
			{
				p->image[j] = 0x1AFF00;
				j++;
				i++;
			}
		}
		p->a = p->a->next;
	}
}

void	print_plist(t_libx *p)
{
//	int i;
//	int j;
	int max;

	
	p->a = get_start_list(p->a);
	p->b = get_start_list(p->b);
	p->pic = mlx_new_image(p->init, get_list_len(p->a) * 2 + 30, get_list_len(p->b));
	ft_printf("%d\n",  (get_list_len(p->a) * 2 + 40) * get_list_len(p->b) * 4);
	p->image = (int*)mlx_get_data_addr(p->pic, &p->bpp, &p->s_l, &p->endian);
	fill_image(p);
	mlx_put_image_to_window(p->init, p->win, p->pic, 20, 20);
	mlx_destroy_image(p->init, p->pic);
	mlx_clear_window(p->init, p->win);
	//ft_printf("################################################################################################\n");
	max = get_nb_elem(p->a) + get_nb_elem(p->b) + 80;
//	print_line(max, 0);
/*	while (p->a)
	{
		i = p->a->is_data ? get_pos(p->a, p->a->data) : 0;
		j = p->b->is_data ? get_pos(p->b, p->b->data) : 0;
		ft_printf("%3d - ", i);
		print_line(i, 1);
		ft_printf("%*c", (get_nb_elem(p->b) + get_nb_elem(p->a) + 8) - i, 0);
		ft_printf("%3d - ", j);
		print_line(j, 1);
		ft_printf("\n");
			//ft_printf("%d %*d\n", p->a->data, p->a->data < 0 ? (40 - ft_nbrlen(p->a->data) - 1)
		//		: (40 - ft_nbrlen(p->a->data)), p->b->data);
		if (!p->a->next)
			break ;
		p->a = p->a->next;
		p->b = p->b->next;
	}
	print_line(max, 0);*/
//	my_sleep(10000000);
//	ft_printf("\e[1;1H\e[2J");
	my_sleep(10000000);
	my_sleep(10000000);
	my_sleep(10000000);
	my_sleep(10000000);
}

int		len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
