/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:54:09 by agesp             #+#    #+#             */
/*   Updated: 2019/02/20 15:30:01 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*my_realloc(char *old_str, char *new_str)
{
	int		i;
	int		j;
	char	*save;

	i = -1;
	j = 0;
	if (!old_str)
		return (NULL);
	if (!new_str)
		return (old_str);
	if (!(save = malloc(sizeof(char) * (ft_strlen(old_str)
			+ ft_strlen(new_str)) + 2)))
		return (NULL);
	while (old_str[++i])
		save[i] = old_str[i];
	save[i++] = '\n';
	while (new_str[j])
		save[i++] = new_str[j++];
	save[i] = '\0';
	free(old_str);
	old_str = NULL;
	return (save);
}

void	free_all(t_lem *p)
{
	if (p && p->instr)
	{
		free(p->instr);
		p->instr = NULL;
	}
	free(p);
	p = NULL;
	exit(1);
}

int		main(int ac, char **av)
{
	t_lem	*p;
	char	*str;

	if (!(p = malloc(sizeof(t_lem))))
		free_all(p);
	p->instr = NULL;
	while (get_next_line(0, &str))
	{
		if (!p->instr)
			p->instr = str;
		else
		{
			if (!(p->instr = my_realloc(p->instr, str)))
			{
				free_all(p);
				free(str);
			}
			if (str && !ft_isdigit(str[0]) && str[0] != '#')
			{
				free(str);
				free_all(p);
			}
			str ? free(str) : do_nothing();
		}
	}
	free(str);
	if (!input_check(p->instr))
		ft_printf("error\n");
	ft_printf("%s\n", p->instr);
	sleep(3);
	return (0);
}		
