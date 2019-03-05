#include "lemin.h"

static t_links	*new_links(void)
{
	t_links	*tmp;

	if (!(tmp = (t_links *)malloc(sizeof(t_links))))
		exit(-1);
	ft_bzero(tmp, sizeof(t_links));
	return (tmp);
}

int 	verif_link(t_rooms *r, t_lemin *e, char *s1)
{
	if (ft_strcmp(e->start->name, s1) == 0 || ft_strcmp(e->end->name, s1) == 0)
		return (0);
	while (r->next != NULL)
	{
		if (ft_strcmp(r->name, s1) == 0)
			break ;
		r = r->next;
	}
	if (r->next == NULL)
		return(1);
	return (0);
}

char			*name_links(char *line, t_links *l)
{
	int 	i;
	char 	*str;

	i = 0;
	while (line[i] != '-' && line[i])
		i++;
	if (!l->s1)
	{
		if (!(str = ft_strsub(line, 0, i)))
			exit(-1);
		else
			return (str);
	}
	else if(!l->s2)
	{
		i++;
		if (!(str = ft_strdup(&line[i])))
			exit(-1);
		else
			return (str);
	}
	else
		exit(-1);
	return (NULL);
}

static void			add_links(t_lemin *e, t_links **l, char *line, int i)
{
	t_links	*tmp;

	tmp = e->l;
	if (!e->l)
	{
		*l = new_links();
		e->l = *l;
		e->l->s1 = name_links(line, e->l);
		e->l->s2 = name_links(line, e->l);
		e->l->n_links = i;
	}
	else
	{
		*l = new_links();
		while (tmp->next != NULL)
		{
			i++;
			tmp = tmp->next;
		}
		(*l)->s1 = name_links(line,	*l);
		(*l)->s2 = name_links(line, *l);
		(*l)->n_links = i;
		e->nb_links = i;
		tmp->next = (*l);
	}
}

void 	parsing_links(char *line, t_lemin *e)
{
	t_links *l;

	if (!ft_strchr(line, '-'))
			exit(-1);
	add_links(e, &l, line, 0);
	if (!ft_strcmp(l->s1, l->s2))
			exit(-1);
	verif_link(e->r, e, l->s1);
	verif_link(e->r, e, l->s2);
}

