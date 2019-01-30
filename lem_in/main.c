/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 13:28:38 by agesp             #+#    #+#             */
/*   Updated: 2019/01/29 16:16:24 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"

typedef struct	s_lem
{
	char *s;
	int is_start;
	int	is_end;
	struct s_lem *next;
}				t_lem;
	
typedef struct	s_ant
{
	int save;
	int is_start;
	int	is_end;
}				t_ant;

void	add_to_list(t_lem *head, char *s, int is_start, int is_end)
{
	while (head->next)
	{
		head = head->next;
	}
	if (!(head->next = malloc(sizeof(s_head))))
		return ;
	head->next->is_start = is_start;
	head->next->is_end = is_end;
	head->next->next = NULL;
	head->next->s = s;
}

int		is_good_com(char *s)
{
	if (s[0] == '#')
	{
		if (!ft_strcmp(str, "##start"))
			return (1);
		if (!ft_strcmp(str, "##start"))
			return (2);
		return (3);
	}
	return (0);

t_lem	*create_list(void)
{
	t_lem	*p;
	t_lem	*head;
	t_ant	*x;
	char	*str;

	p = NULL;
	head = NULL;
	if (!(p = malloc(sizeof(t_lem))))
		return (perror("malloc fail"));
	if (!(x = malloc(sizeof(t_ant))))
		return (perror("malloc fail"));
	while (get_next_line(0, &str) > 0)
	{
		x->save = is_good_com(str);
		x->is_start = x->save == 1 && x->is_start == 0 ? 1 : 0;
		x->is_end = x->save == 2 && x->is_end == 0 ? 1 : 0;
		x->save
	head = p;
}
int		main(int ac, char **av)
{
	char *str;

	str = NULL;
	if (ac == 1)
	{
		get_next_line(0, &str);
		while (str[0] && str[0] == "#")
		p->s = str;
		head = p;
		while (get_next_line(0, &str) > 0)
		{
			add_to_
		}
	}
	return (0);
}
