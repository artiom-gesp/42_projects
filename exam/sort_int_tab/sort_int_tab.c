/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:47:12 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 15:03:45 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sort_int_tab(int *tab, unsigned int size)
{
	int i;
	int	save;

	i = 0;
	save = 0;
	while (i < (int)size - 1)
	{
		if (i >= 0 && tab[i] > tab[i + 1])
		{
			while (i >= 0 && tab[i] >= tab[i + 1])
			{
				save = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = save;
				i--;
			}
		}
		i++;
	}
}
