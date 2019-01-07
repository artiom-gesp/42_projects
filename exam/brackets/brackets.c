/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:21:44 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 15:45:17 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		is_ok(char z, char c)
{
	if (c == '(' && z == ')')
		return (1);
	else if (c == '{' && z == '}')
		return (1);
	else if (c == '[' && z == ']')
		return (1);
	return (0);
}

int		brackets(char *str)
{
	int		i;
	int		j;
	char	buff[4086];

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
			buff[++j] = str[i];
		if (str[i] == ')' || str[i] == '}' || str[i] == ']')
			if (!is_ok(str[i], buff[j--]))
				return (0);
		i++;
	}
	return (j ? 0 : 1);
}

int		main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		write(1, "\n", 1);
	else
	{
		while (i < ac)
		{
			if (brackets(av[i]))
				write(1, "OK\n", 3);
			else
				write(1, "Error\n", 6);
			i++;
		}
	}
	return (0);
}
