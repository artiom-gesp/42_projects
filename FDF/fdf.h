/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 11:27:33 by agesp             #+#    #+#             */
/*   Updated: 2019/01/19 16:39:02 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/ft_printf.h"
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
	char 		*save;
	int			tab[5000][5000];
}				t_fstruct;

void	print_seg(t_line *line, t_fstruct *p);

#endif
