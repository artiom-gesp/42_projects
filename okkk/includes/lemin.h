#ifndef LEMIN_H
# define LEMIN_H
# include "../libft/libft.h"

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
	int 			nb_links;
	int 			nb_start;
	int 			nb_end;
	int				**map;
	struct s_rooms  *r;
	struct s_ants	*a;
	struct s_rooms   **table_r;
	struct s_links	*l;
	struct s_hash	**h;
	struct s_rooms	*start;
	struct s_rooms	*end;
	struct s_info	*i;
	struct s_path	*head_to_p;
	struct s_path	*p;
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
	struct s_ants	*next;
}					t_ants;


typedef	struct 		s_info
{
	char 			*line;
	struct s_info	*next;
}					t_info;

typedef struct 		s_path
{
	int 			*path;
	int				size_path;
	//	int 			color;
	//	int 			dist;
	struct s_path	*next;
}					t_path;

int				**created_map(t_lemin *e);
int				reader(t_lemin *e);
int				router_links(t_lemin **e, char *line);
t_rooms			*created_lst(void);
int				created_links(t_links **tmp, t_rooms *r, char *line, t_lemin *e);
t_links			*ft_init_links(void);
void			add_info(t_lemin *lem_in, t_info **info, char *line);
void			parsing_ants(t_lemin *e, char *line);
void			parsing_rooms(char *line, t_lemin *e, enum pos *d);
void			parsing_links(char *line, t_lemin *e);
void 			parsing_duplicate_rooms(t_rooms *r, t_rooms *v);
void			parsing_links_unknow(t_links *l, t_rooms *r);
void			created_hastable(t_lemin *e);
int				generate_hash(char *str, int nb_rooms);
void			bfs(t_lemin *e);

void			pop_stack(int *stack, int nb_rooms);
int				add_path(int *prev, t_lemin *e);
int				get_nb_links(t_lemin *e, int x);
void			create_path(t_lemin *e, int *path, int len);
void			push_stack(int *stack, t_lemin *e, int *prev);

#endif
