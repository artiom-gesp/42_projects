/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:31:29 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/02 12:02:13 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"

enum pos
{
	ANTS,
	ROOMS,
	LINKS
};

typedef struct 		s_lemin
{
	int				x;
	int				y;
	char			*av;
	int 			nb_ants;
	int 			st;
	int 			nd;
	int 			nb_rooms;
	int				nb_paths;
	int 			max_sizep;
	int 			nb_links;
	int 			nb_start;
	int 			nb_end;
	int				**map;
	int				*stack;
	int				*map_stack;
	int				*visited;
	int				*map_visited;
	int				*prev;
	int				*map_prev;
	int				*find_new;
	int				*map_fn;
	int 			maxy;
	int 			maxx;
	int 			minx;
	int 			conti;
	int 			miny;
	char 			**map_v;
	int				max_lines;
	struct s_rooms  *r;
	struct s_ants	*a;
	struct s_rooms  **table_r;
	struct s_links	*l;
	struct s_hash	**h;
	struct s_rooms	*start;
	struct s_rooms	*end;
	struct s_info	*i;
	struct s_path	*p;
	struct s_path	*select_p;
}					t_lemin;

typedef struct 		s_rooms
{
	int 			occuped;
	int				nb_rooms;
	int 			etage;
	unsigned int 	key;
	int				x;
	int				y;
	char			*name;
	struct s_rooms	*next;
}					t_rooms;

typedef struct 		s_links
{
	int				n_links;
	char			*s1;
	char			*s2;
	struct s_links	*next;
}					t_links;

typedef struct 		s_hash
{
	int				key;
	struct s_rooms	*r;
}					t_hash;


typedef	struct 		s_ants
{
	int				nb_ants;
	int 			color;
	int 			x;
	int 			y;
	struct s_path	*p;
	struct s_ants	*next;
	struct s_ants 	*prev;
}					t_ants;


typedef	struct 		s_info
{
	char 			*line;
	struct s_info	*next;
}					t_info;

typedef struct 		s_path
{
	int 			i;
	int 			*path;
	int 			conti;
	int				s_conti;
	int 			stop;
	int				size_path;
	int				steps;
	int 			nb_ants;
	int				capacity;
	struct s_path	*next;
}					t_path;
void 		affiche_map(t_lemin *e, int **map);

void			created_map(t_lemin *e);
int				reader(t_lemin *e);
int				router_links(t_lemin **e, char *line);
t_rooms			*created_lst(void);
int				created_links(t_links **tmp, t_rooms *r, char *line, t_lemin *e);
t_links			*ft_init_links(void);
void			add_info(t_lemin *e, char *line);
void			parsing_ants(t_lemin *e, char *line);
void			parsing_rooms(char *line, t_lemin *e, enum pos *d);
void			parsing_links(char *line, t_lemin *e);
void 			parsing_duplicate_rooms(t_rooms *r, t_rooms *v);
void			parsing_links_unknow(t_links *l, t_rooms *r);
void			created_hastable(t_lemin *e);
int				generate_hash(char *str, int nb_rooms);
void			bfs(t_lemin *e);
void			pop_stack(t_lemin *e, int nb_rooms, int flag);
int				add_path(t_lemin *e);
int				get_nb_links(t_lemin *e, int x);
void			create_path(t_lemin *e, int *path, int len);
void			push_stack(t_lemin *e, int flag);
void			visu(t_lemin *l);
void			move_ants_forward(t_lemin *e);
void 			add_end_start(t_lemin *e);
t_rooms			*new_rooms(void);
void			coor_room(char *line, int i);
int				paths_remain(t_lemin *e);
int				is_stack_empty(int *stack, int len);
void			set_bfs_base_var(t_lemin *e);
void			print_paths(t_lemin *e, t_path *sa);
int 			set(t_path *p, int **map, int c);
int 			condition(t_path *p, t_path *ok, int **map, int count);
void 			zero_vistid(t_lemin *e);
//void 			free_path(t_path **p);
void			select_paths(t_lemin *e);
void			setup_map(t_lemin *e);
int				get_len(t_lemin *e);
void			set_path_capacity(t_lemin *e);
void			reset_tab(t_lemin *e);
void			reset_map_tab(t_lemin *e);
void			create_single(t_lemin *e);
void			control_stack(t_lemin *e, int x);
t_path			*free_path(t_path *p, int realloc);
#endif
