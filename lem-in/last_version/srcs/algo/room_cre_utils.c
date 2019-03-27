/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_cre_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 09:55:09 by agesp             #+#    #+#             */
/*   Updated: 2019/03/18 10:56:40 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_rooms		*new_rooms(void)
{
	t_rooms	*tmp;

	if (!(tmp = malloc(sizeof(t_rooms))))
		exit(-1);
	ft_bzero(tmp, sizeof(t_rooms));
	return (tmp);
}

void		coor_room(char *line, int i)
{
	if (ft_isdigit(line[i]))
	{
		while (ft_isdigit(line[i]))
			i++;
		i++;
		if (!ft_isdigit(line[i]))
			exit(-1);
	}
	else
		exit(-1);
	while (ft_isdigit(line[i]))
		i++;
	if (!line[i])
		return ;
	else
		exit(-1);
}
