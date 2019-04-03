/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:59:12 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:59:14 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H
# include "libft.h"
# include "../minilibx_macos/mlx.h"
# define WIDTH 1400
# define HEIGHT 1200
# include "lemin.h"

typedef struct			s_image
{
	void				*img;
	char				*img_data;
	int					img_bpp;
	int					img_size_line;
	int					img_endian;
}						t_image;

typedef	struct			s_event
{
	int					pause;
	int					zoom;
	int					color;
}						t_event;

typedef struct			s_design
{
	int					fx;
	int					fy;
	int					x;
	int					y;
}						t_design;

typedef	struct			s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img;
	int					color;
	int 				pace;
	int 				tmpspacew;
	int 				wspace;
	int 				hspace;
	int 				affiche;
	int 				name;
	char 				**mv_ants;
	struct s_design		*d;
	struct s_event		*even;
	struct s_image		*image;
	struct s_lemin 		*e;
	struct s_ants 		*a;
}						t_mlx;

t_design				*init_design(int x, int y, int fy, int fx);
void					img_pixel_put(t_mlx *e, int x, int y);
void					clear_image(t_mlx *e);
void					design_windows(t_mlx *e);
void					info(t_mlx *v);
void					function_color(t_design *d, t_mlx *e);
int						deal_key(int key, t_mlx *e);
void 					viewer(t_mlx *v);

#endif
