/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:31:29 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/08 16:38:49 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"
# define INT_MAX  2147483647

enum				e_pos
{
	ANTS,
	ROOMS,
	START,
	END,
	LINKS
};

typedef	struct		s_info
{
	char			*line;
	struct s_info	*next;
}					t_info;

typedef struct		s_rooms
{
	char			*name;
	long			dist;
	int				status;
	int				id_r;
	int				nb_links;
	int				x;
	int				y;
	int				occuped;
	struct s_rooms	**links;
	struct s_rooms	*r_p;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_hash
{
	int				key;
	struct s_rooms	*r;
}					t_hash;

typedef	struct		s_ants
{
	int				nb_ants;
	int				color;
	int				x;
	int				y;
	struct s_path	*p;
	struct s_ants	*next;
}					t_ants;

typedef struct		s_path
{
	int				i;
	int				ok;
	int				*path;
	int				conti;
	int				s_conti;
	int				stop;
	int				size_path;
	int				steps;
	int				nb_ants;
	int				capacity;
	struct s_path	*next;
}					t_path;

typedef struct		s_lemin
{
	int				**map;
	int				*stack;
	int				*map_stack;
	int				*visited;
	int				*map_visited;
	int				*prev;
	int				*map_prev;
	int				*find_new;
	int				*map_fn;
	int				max_lines;
	int				x;
	int				y;
	char			*av;
	int				nb_ants;
	int				nb_rooms;
	int				nb_paths;
	int				n;
	int				stop;
	struct s_path	*select_p;
	struct s_rooms	*r;
	struct s_ants	*a;
	struct s_rooms	**table_r;
	struct s_hash	**h;
	struct s_rooms	*start;
	struct s_rooms	*end;
	struct s_info	*i;
	struct s_path	*p;
}					t_lemin;

void				links_rooms(t_lemin *e);
void				reader(t_lemin *e);
void				add_info(t_lemin *e, char *line);
char				*name_rooms(t_lemin *e, char *line, char c);
t_rooms				*new_rooms(t_lemin *e);
void				parsing_rooms(t_lemin *e, char *line, int i);
void				rooms(char *line, t_lemin *e, enum e_pos *d);
int					parsing_links(char *line, t_lemin *e);
t_rooms				**table_rooms(t_lemin *e);
void				created_hastable(t_lemin *e);
void				parsing_ants(t_lemin *e, char *line);
long long			generate_hash(char *str, int nb_rooms);
void				lem_in_error(t_lemin *e, int error);
void				move_ants_forward(t_lemin *e, t_path *p, t_ants *a);
void				bfs(t_lemin *e);
void				pop_stack(t_lemin *e, int nb_rooms, int flag);
int					add_path(t_lemin *e);
int					get_nb_links(t_lemin *e, int x);
void				create_path(t_lemin *e, int *path, int len);
void				push_stack(t_lemin *e, int flag);
int					paths_remain(t_lemin *e);
int					is_stack_empty(int *stack, int len);
void				set_bfs_base_var(t_lemin *e);
void				print_paths(t_lemin *e, t_path *sa);
int					set(t_path *p, int **map, int c);
int					condition(t_path *p, t_path *ok, int **map, int count);
void				zero_vistid(t_lemin *e);
void				select_paths(t_lemin *e);
void				setup_map(t_lemin *e);
int					get_len(t_lemin *e);
void				set_path_capacity(t_lemin *e);
void				reset_tab(t_lemin *e);
void				reset_map_tab(t_lemin *e);
void				create_single(t_lemin *e);
void				control_stack(t_lemin *e, int x);
t_path				*free_path(t_path *p, int realloc, t_lemin *e);
void				free_ants(t_lemin *e);
void				path_fun_free(t_lemin *e);
void				free_info(t_lemin *e);
void				free_rooms(t_rooms *p);
void				free_hash(t_lemin *e);
void				visu(t_lemin *e);
int					still_paths(t_lemin *e);
void				free_map1(t_lemin *e);
void				malloc_move(t_lemin *e, t_path *p);
int					not_all_printed(t_ants *a);
void				zero_ants(t_lemin *e);

#endif
