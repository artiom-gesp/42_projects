/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:06:18 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 13:18:24 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		check_before(char *s1, char c, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (s1[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	inter(char *s1, char *s2)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (check_before(s1, s1[i], i))
		{
			j = 0;
			while (s2[j] && s2[j] != s1[i])
				j++;
			if (s2[j] == s1[i])
				write(1, &s1[i], 1);
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 3)
		inter(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}
