/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_threw_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:50:22 by agesp             #+#    #+#             */
/*   Updated: 2019/01/09 13:54:35 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_push	*get_start_list(t_push *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

t_push	*get_end_list(t_push *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

t_push	*get_top_list(t_push *list)
{
	list = get_start_list(list);
	while (list->next && !list->is_data)
	{
		list = list->next;
	}
	return (list);
}
