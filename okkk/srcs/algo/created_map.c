#include "lemin.h"

void	connexion_map( t_lemin *e, char *s1, char *s2, int **map)
{
	int key1;
	int key2;

	key2 = generate_hash(s2, e->nb_rooms);
	key1 = generate_hash(s1, e->nb_rooms);
	map[e->h[key1]->r->nb_rooms][e->h[key2]->r->nb_rooms] = 1;	
	map[e->h[key2]->r->nb_rooms][e->h[key1]->r->nb_rooms] = 1;
}

void	created_liasion_map(int **map, t_lemin *e)
{
	int y;
	
	y = 0;
	while (y < e->nb_rooms)
	{
		map[y][y] = 2;
		y++;
	}
}

int		**created_map(t_lemin *e)
{
	int 	**map;
	t_rooms *r;
	t_links *l;
	int 	i;

	i = 0;
	r = e->r;
	l = e->l;
	if (!(map = malloc(sizeof(int **) * e->nb_rooms)))
		return (NULL);
	while (i < e->nb_rooms)
	{
		if (!(map[i] = malloc(sizeof(int *) * e->nb_rooms)))
			return NULL;
		map[i][e->nb_rooms] = 0;
		map[i] = ft_memset(map[i], 0, e->nb_rooms - 1);
		i++;
	}
	map[e->nb_rooms] = NULL;
	while (l)
	{
		connexion_map(e, l->s1, l->s2, map);
		l = l->next;
	}
	return (map);
}