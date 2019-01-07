/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:42:53 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 16:56:01 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int		pgcd(int nb1, int nb2)
{
	int i;
	int save;

	save = 1;
	i = 1;
	while (i <= nb1 && i <= nb2)
	{
		if ((nb1 % i == 0) && (nb2 % i == 0))
			save = i;
		i++;
	}
	return (save);
}

int		main(int ac, char **av)
{
	int nb1;
	int nb2;

	if (ac == 3)
	{
		nb1 = atoi(av[1]);
		nb2 = atoi(av[2]);
		printf("%d\n", pgcd(nb1, nb2));
	}
	else
	{
		printf("\n");
	}
}
