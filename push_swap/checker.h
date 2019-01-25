/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:44:18 by agesp             #+#    #+#             */
/*   Updated: 2019/01/25 17:06:12 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft/ft_printf.h"
# include "mlx.h"

typedef struct		s_push
{
	struct s_push	*next;
	struct s_push	*prev;
	int				is_data;
	int				data;
	int				color;
}					t_push;

typedef struct		s_libx
{
	void	*init;
	void	*win;
	void	*pic;
	int		bpp;
	int		*image;
	int		s_l;
	int		endian;
	t_push	*a;
	t_push	*b;
}					t_libx;

t_push				*get_start_list(t_push *list);
t_push				*get_top_list(t_push *list);
t_push				*get_end_list(t_push *list);
int					get_nb_elem(t_push *p);
void				swap(t_push *p, int print, int which);
void				swap_both(t_push *a, t_push *b, int print);
void				get_color(t_push *a, t_push *b, char *instrcution);
void				push(t_push *a, t_push *b, int print, int which);
char				**create_tab(int ac, char **av);
void				rotate(t_push *p, int print, int which);
void				rev_rotate(t_push *p, int print, int which);
void				rotate_both(t_push *a, t_push *b, int print);
void				rev_rotate_both(t_push *a, t_push *b, int print);
void				free_tab(char **tab);
char				**add_el_ttab(char **ptr, char *str);
int					do_check(t_push *a, t_push *b, char *instruction);
void				print_plist(t_libx *p);
int					is_full(t_push *list);
int					is_sorted(t_push *list);
int					is_rev_sorted(t_push *list);
t_push				*fill_pile(int ac, char **av, int is_data);
void				free_list(t_push *list);
int					is_input_ok(int ac, char **av);
void				push_swap(t_push *a, t_push *b);
int					get_mediane(t_push *a, t_push *b, int print);
int					get_list_len(t_push *p);
int					is_smallest(t_push *p);
t_push				*copy_pile(t_push *p, int is_data);
int					is_empty(t_push *list);
int					len_tab(char **tab);
void				quick_sort(t_push *a, t_push *b);
void				nquick_sort(t_push *a, t_push *b);
void				sort_five(t_push *a, t_push *b);
int					get_direction(t_push *p);
void				sort_three(t_push *a, int print);
int					is_max(t_push *p, int data);
int					is_min(t_push *p, int data);
int					get_nb_elem(t_push *p);
int					get_borne(t_push *p, int mediane, int *borne);
void				super_sort(t_push *a, t_push *b, t_push *c);

#endif
