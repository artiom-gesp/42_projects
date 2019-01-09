/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:54:23 by agesp             #+#    #+#             */
/*   Updated: 2019/01/09 16:26:08 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**add_el_ttab(char **ptr, char *str)
{
	int		i;
	char	**tab;

	i = 0;
	while (ptr[i])
		i++;
	if (!(tab = malloc(i + 1)))
		return (NULL);
	i = 0;
	while (ptr[i])
	{
		if (!(tab[i] = malloc(sizeof(char*) * (int)ft_strlen(ptr[i]))))
			return (0);
		ft_strcpy(tab[i], ptr[i]);
		i++;
	}
	if (!(tab[i] = malloc(sizeof(char*) * (int)ft_strlen(str))))
			return (0);
	tab[i] = ft_strcpy(tab[i], str);
	tab[i + 1] = NULL;
	free_tab(ptr);
	return (tab);
}	
