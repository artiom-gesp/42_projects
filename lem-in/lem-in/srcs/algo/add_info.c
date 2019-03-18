#include "../includes/lemin.h"

static t_info	*new_info(void)
{
	t_info	*tmp;

	if (!(tmp = (t_info *)malloc(sizeof(t_info))))
		exit(-1);
	ft_bzero(tmp, sizeof(t_info));
	return (tmp);
}

void			add_info(t_lemin *e, char *line)
{
	t_info	*tmp;

	if (!e->i)
	{
		e->i = new_info();
		if (!(e->i->line = ft_strdup(line)))
			exit(-1);
		e->i->next = NULL;
	}
	else
	{
		tmp = e->i;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_info();
		if (!(tmp->next->line = ft_strdup(line)))
			exit(-1);
		tmp->next->next = NULL;
	}
}
