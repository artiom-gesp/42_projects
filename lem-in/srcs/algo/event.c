/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:37:30 by kecosmon          #+#    #+#             */
/*   Updated: 2019/03/18 10:48:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void		back_ants(t_mlx *v)
{
	t_ants *a;

	a = v->e->a;
	while (a)
	{
		if (a->p->i > 1)
			a->p->i -= 1;
		if (a->p->i == 0)
			a->p->i = 1;
		a = a->next;
	}
}

void		prec_ants(t_mlx *v)
{
	t_ants *a;

	a = v->e->a;
	while (a)
	{
		if (a->p->ok == 1)
			a->p->i++;
		else if (a->p->i >= a->p->size_path)
			a->p->i++;
		a = a->next;
	}
}

int			deal_key(int key, t_mlx *v)
{
	if (key == 53)
		free_visu(v);
	if (key == 20)
		v->affiche = 1;
	if (key == 21)
		v->affiche = 0;
	if (key == 18)
		v->name = 1;
	if (key == 124)
	{
		v->e->n++;
		prec_ants(v);
	}
	if (key == 123 && v->e->n > 0)
	{
		v->e->n--;
		back_ants(v);
	}
	mlx_clear_window(v->mlx_ptr, v->win_ptr);
	viewer(v);
	design_windows(v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->image->img, 0, 0);
	info(v);
	return (0);
}
