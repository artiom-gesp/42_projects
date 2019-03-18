#include "../includes/lemin.h"

static t_info	*new_info(void)
{
	t_info	*tmp;

	if (!(tmp = (t_info *)malloc(sizeof(t_info))))
		exit(-1);
	ft_bzero(tmp, sizeof(t_info));
	return (tmp);
}

void			add_info(t_lemin *e, t_info **info, char *line)
{
	t_info	*tmp;

	tmp = e->i;
	if (!e->i)
	{
		*info = new_info();
		e->i = *info;
		if (!(e->i->line = ft_strdup(line)))
			exit(-1);
	}
	else
	{
		*info = new_info();
		if (!((*info)->line = ft_strdup(line)))
			exit(-1);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (*info);
	}
}