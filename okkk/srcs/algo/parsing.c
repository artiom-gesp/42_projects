#include "lemin.h"

void		parsing_links_unknow(t_links *l, t_rooms *r)
{
	t_rooms *tmp;
	int 	i;

	tmp = r;
	while (l)
	{
		i = 0;
		r = tmp;
		while (r)
		{
			if (!ft_strcmp(l->s1, r->name) || !ft_strcmp(l->s2, r->name))
				i++;
			r = r->next;
		}
		if (i > 2)
			exit(-1);
		l = l->next;
	}
}

void 		parsing_duplicate_rooms(t_rooms *r, t_rooms *v)
{
	int 	i;
	t_rooms *tmp;
	
	i =0;

	tmp = r;
	if (tmp)
	while (v->next != NULL)
	{
		r = tmp;
		while (r->next != NULL)
		{
			if (!ft_strcmp(v->name, r->name))
				i++;
			if (i > 1)
				exit(-1);
			r = r->next;
		}
		i = 0;
		v = v->next;
	}
}