/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 11:27:33 by agesp             #+#    #+#             */
/*   Updated: 2019/04/19 13:55:31 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_printf.h"
# include "mlx.h"

typedef struct	s_line
{
	int			xi;
	int			xf;
	int			yi;
	int			yf;
	long long	color;
	int			dx;
	int			dy;
	int			xplus;
	int			yplus;
	int			both;
	int			x;
	int			y;
}				t_line;

typedef struct	s_fstruct
{
	int			x;
	int			y;
	int			zoom;
	void		*init;
	void		*win;
	t_line		*line;
	char		*save;
	int			tab[5000][5000];
	int			min;
	int			max;
	int			contrast;
}				t_fstruct;

void			print_seg(t_line *line, t_fstruct *p);
int				get_tab_len(char **tab);
int				is_tab_ok(char **tab, int x);
void			copy_into_tab(int tab[5000][5000], char **tab2);
void			print_iso(t_fstruct *p, t_line *line);
int				create_tab(char *file, t_fstruct *p);
void			print_para(t_fstruct *p, t_line *line);
long			ft_map(long x, t_fstruct *p, long out_min, long out_max);
int				get_max(t_fstruct *p);
int				get_min(t_fstruct *p);
int				deal_key(int key, void *param);

#endif
