/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:44:18 by agesp             #+#    #+#             */
/*   Updated: 2019/01/10 11:59:01 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft/ft_printf.h"

typedef struct		s_push
{
	struct s_push	*next;
	struct s_push	*prev;
	int				is_data;
	int				data;
}					t_push;

t_push				*get_start_list(t_push *list);
t_push				*get_top_list(t_push *list);
t_push				*get_end_list(t_push *list);
void				swap(t_push *p);
void				swap_both(t_push *a, t_push *b);
void				push(t_push *a, t_push *b);
void				rotate(t_push *p);
void				rev_rotate(t_push *p);
void				rotate_both(t_push *a, t_push *b);
void				rev_rotate_both(t_push *a, t_push *b);
void				free_tab(char **tab);
char				**add_el_ttab(char **ptr, char *str);
int					do_check(t_push *a, t_push *b,
		char *instruction, int flag);
void				print_plist(t_push *a, t_push *b);
int					is_full(t_push *list);
int					is_sorted(t_push *list);
int					is_rev_sorted(t_push *list);
t_push				*fill_pile(int ac, char **av, int is_data);
void				free_list(t_push *list);
int					is_input_ok(char ac, char **av);

#endif
