#include "../includes/lemin.h"

static t_ants	*new_ants(void)
{
	t_ants	*tmp;

	if (!(tmp = (t_ants *)malloc(sizeof(t_ants))))
		exit(-1);
	ft_bzero(tmp, sizeof(t_ants));
	return (tmp);
}

static void			add_ants(t_lemin *e, t_ants **ants, int i)
{
	t_ants	*tmp;

	tmp = e->a;
	if (!e->a)
	{
		*ants = new_ants();
		e->a = *ants;
		e->a->nb_ants = i;
	}
	else
	{
		*ants = new_ants();
		(*ants)->nb_ants = i;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (*ants);
	}
}

void		parsing_ants(t_lemin *e, char *line)
{
	int		i;
	t_ants 	*ants;

	i = 0;
	if (line[i] == '+')
		i++;
	else if (line[i] == '-')
	{
		exit(-1);
	}
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != 0)
	{
		ft_strdel(&line);
		exit(-1);
	}
	e->nb_ants = ft_atoi(line);
	i = 0;
	while (++i < e->nb_ants + 1)
		add_ants(e, &ants, i);
}
