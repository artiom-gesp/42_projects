/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:54:09 by agesp             #+#    #+#             */
/*   Updated: 2019/02/23 16:47:42 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem_in.h"

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

void	free_all(t_lem *p, t_arg *l, char *error)
{
	if (p && p->instr)
	{
		free(p->instr);
		p->instr = NULL;
	}
	if (l && l->arg)
	{
		free(l->arg);
		l->arg = NULL;
	}
	free(p);
	free(l);
	l = NULL;
	p = NULL;
	if (ft_strcmp(error, "Ok"))
		ft_printf("%s\n", error);
	exit(1);
}

void	create_str(t_lem *p, t_arg *l)
{
	char	*str;

	(void)p;
	while (get_next_line(0, &str))
	{
		if (!l->arg)
			l->arg = str;
		else
		{
			if (!(l->next = malloc(sizeof(t_arg))))
				free_all(p, l, "Malloc fail :(");
			l = l->next;
			l->arg = str;
		}
	}
}

int		main(void)
{
	t_lem	*p;
	t_arg	*l;

	p = NULL;
	l = NULL;
	if (!(p = malloc(sizeof(t_lem))))
		free_all(p, l, "Malloc fail :(");
	if (!(l = malloc(sizeof(t_arg))))
		free_all(p, l, "Malloc fail :(");
	p->instr = NULL;
	l->arg = NULL;
	create_str(p, l);
	ft_printf("%d\n", input_check(l));
	while (l)
	{
		ft_printf("%s\n", l->arg);
		if (!l->next)
			break ;
		l = l->next;
	}
//	if (argument_check(p->instr) == -1)
//		free_all(p, l, "Wrong input");
	free_all(p, l, "Ok");
	return (0);
}		
