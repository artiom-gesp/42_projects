#include "lemin.h"

static t_rooms	*new_rooms(void)
{
	t_rooms	*tmp;

	if (!(tmp = (t_rooms *)malloc(sizeof(t_rooms))))
		exit(-1);
	ft_bzero(tmp, sizeof(t_rooms));
	return (tmp);
}

static	void		coor_room(t_rooms **r, char *line, int i)
{
	if (ft_isdigit(line[i]))
	{
		(*r)->x = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		i++;
		if (ft_isdigit(line[i]))
			(*r)->y = ft_atoi(&line[i]);
		else
			exit(-1);
	}
	else
		exit(-1);
	while (ft_isdigit(line[i]))
			i++;
	if (!line[i])
		return ;
	else
		exit(-1);
}

char				*name_rooms(char *line)
{
	int 	i;
	char 	*str;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	if (!(str = ft_strsub(line, 0, i)))
		exit(-1);
	return (str);
}

static void			add_rooms(t_lemin *e, t_rooms **rooms, char *line, int i)
{
	t_rooms	*tmp;

	tmp = e->r;
	if (!e->r)
	{
		*rooms = new_rooms();
		e->r = *rooms;
		e->r->name = name_rooms(line);
		e->r->nb_rooms = 0;
		e->nb_rooms++;
	}
	else
	{
		*rooms = new_rooms();
		while (tmp->next != NULL)
		{
			i++;
			tmp = tmp->next;
		}
		(*rooms)->nb_rooms = i;
		e->nb_rooms++;
		(*rooms)->name = name_rooms(line);
		tmp->next = (*rooms);
	}
}

static void			add_start(t_lemin *e, t_rooms **rooms, char *line)
{
	t_rooms	*tmp;

	tmp = e->start;
	if (!e->start)
	{
		*rooms = new_rooms();
		e->start = *rooms;
		e->start->name = name_rooms(line);
		e->start->nb_rooms = e->nb_rooms;
	}
}

static void			add_end(t_lemin *e, t_rooms **rooms, char *line)
{
	t_rooms	*tmp;

	tmp = e->end;
	if (!e->end)
	{
		*rooms = new_rooms();
		e->end = *rooms;
		e->end->name = name_rooms(line);
		e->end->nb_rooms = e->nb_rooms;
	}
}

void			parsing_rooms(char *line, t_lemin *e, enum pos *d)
{
	t_rooms *r;
	int 	i;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	if (line[0] == 'L')
		exit(-1);
	if (!line[i])
	{
		*d = LINKS;
		parsing_links(line, e);
		return ;
	}
	if (e->st == 1)
	{
		add_start(e, &r, line);
		e->st = 0;
	}
	else if (e->nd == 1)
	{
		add_end(e, &r, line);
		e->nd = 0;
	}
	add_rooms(e, &r, line, 1);
	i++;
	coor_room(&r, line, i);
}