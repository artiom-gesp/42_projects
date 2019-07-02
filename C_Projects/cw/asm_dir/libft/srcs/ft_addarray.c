/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:38:26 by amanuel           #+#    #+#             */
/*   Updated: 2018/12/27 16:36:54 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		**ft_addarray(void **tab, void *array)
{
	int		i;
	int		j;
	void	**fresh;

	if (!array)
		return (tab);
	i = ft_tablen(tab);
	fresh = ft_tabnew(i + 1, 0, 0);
	j = 0;
	if (i && --j)
	{
		while ((tab)[++j])
			fresh[j] = (tab)[j];
		free(tab);
		tab = NULL;
	}
	fresh[j] = array;
	array = NULL;
	return (fresh);
}
