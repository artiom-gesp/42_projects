/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 11:06:59 by agesp             #+#    #+#             */
/*   Updated: 2019/01/23 11:22:45 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_min(t_fstruct *p)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = p->tab[0][0];
	while (i < p->x)
	{
		j = 0;
		while (j < p->y)
		{
			if (p->tab[i][j] < ret)
				ret = p->tab[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}

int		get_max(t_fstruct *p)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = p->tab[0][0];
	while (i < p->x)
	{
		j = 0;
		while (j < p->y)
		{
			if (p->tab[i][j] > ret)
				ret = p->tab[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}

int		deal_key(int key, void *param)
{
	(void)param;
	if (key == 53)
		exit(1);
	return (0);
}
