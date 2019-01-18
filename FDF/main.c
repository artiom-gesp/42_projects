/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:59:04 by agesp             #+#    #+#             */
/*   Updated: 2019/01/18 18:15:09 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft/ft_printf.h"

int	deal_key(int key, void **param)
{
	static int i = 200;
	static int j = 200;
	if (key == 53)
		exit(0);
	else if (key == 12)
	{
		mlx_pixel_put(param[0], param[1], i, j, 0x00FFFF);
		i++;
	}
	else if (key == 13)
	{
		mlx_pixel_put(param[0], param[1], i, j, 0xCC0066);
		j++;
	}
	ft_printf("%d\n", key);
	return (0);
}

int	print_tab(void **param)
{
	int i;
	int j;

	mlx_pixel_put(param[0], param[1], i, j, 0xCC0066);
	return (0);
}

int	get_tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_tab_ok(char **tab, int x)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!ft_isdigit(tab[i][0]))
			return (0);
		i++;
	}
	if (i != x && x != -1)
		return (0);
	return (1);
}

void	copy_into_tab(int z, int tab[][z], char **tab2)
{
	int i;
	static int y = 0;

	i = 0;
	while (tab2[i])
	{
		tab[i][y] = ft_atoi(tab2[i]);
		i++;
	}
	y++;
}

void	print_square(void **param, int x, int y, long long color)
{
	int i;
	int j;

	i = x;
	j = y;
//	while (i < x + 5)
//	{
//		j = y;
//		while (j < y + 5)
//		{
			mlx_pixel_put(param[0], param[1], i, j, color);
//			j++;
//		}
//		i++;
//	}
}

void	trace_seg(int x1, int x2, int y1, int y2, void **param)
{
	double a;
	double b;

	a = (double) ((y2 - y1)) / ((x2 - x1));
	b = y1 - a * x1;
	while (x1 <= x2)
	{
		y1 = a * x1   + b;
		mlx_pixel_put(param[0], param[1], x1 , (int)y1, 0x66FFFF);
		x1++;
	}
}

void ligne(int xi,int xf,int yi,int yf, void **param, long long color) 
{
	int dx,dy,i,xinc,yinc,cumul,x,y ;
	x = xi ;
	y = yi ;
	dx = xf - xi ;
	dy = yf - yi ;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	dx = abs(dx) ;
	dy = abs(dy) ;
	mlx_pixel_put(param[0], param[1], x, y, color) ;
	if ( dx > dy ) 
	{
		cumul = dx / 2 ;
		for ( i = 1 ; i <= dx ; i++ )
		{
			x += xinc ;
			cumul += dy ;
			if ( cumul >= dx ) 
			{
				cumul -= dx ;
				y += yinc ; 
			}
			mlx_pixel_put(param[0], param[1], x, y, color); 
		} 
	}
	else 
	{
		cumul = dy / 2 ;
		for ( i = 1 ; i <= dy ; i++ ) 
		{
			y += yinc ;
			cumul += dx ;
			if ( cumul >= dy ) 
			{
				cumul -= dy ;
				x += xinc ; 
			}
			mlx_pixel_put(param[0], param[1], x, y, color) ; 
		} 
	}
}

int	get_mouse(int intput, int x, int y, void *param)
{
	//printf("%d %d\n", x, y);
	//	mxl_mouse_hook(param[0],  
	return (0);
}

int	do_stuff(int x, int y, char *file, void **param)
{
	int i;
	int j;
	int fd;
	int tab[x][y];
	char *line;

	i = 0;
	j = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		copy_into_tab(y, tab, ft_strsplit(line, ' '));
	}
	i = 0;
	j = 0;
	while (i < y)
	{
		j = 0;
		while (j < x - 1)
		{
			mlx_pixel_put(param[0], param[1], (j - i) * 60 + 500, (j + i) * 30 + 200 , 0x66FFF);
			ligne((j - i) * 60 + 500 - tab[j][i], (j - i + 1) * 60 + 500 - tab[j + 1][i], (j + i) * 30 + 200,
					(j + i + 1) * 30 + 200, param, tab[j][i] != tab[j + 1][i] ? 0x66FFF: 0xFFFFF);
			j += 1;
		}
		i += 1;
	}
	i = 0;
	j = 0;
	while (i < x)
	{
		j = 0;
		while (j < y - 1)
		{
			//mlx_pixel_put(param[0], param[1], (j - i) * 60 + 500, (j + i) * 30 + 200 , 0x66FFF);
			ligne((i - j) * 60 + 500 + tab[i][j], (i - (j + 1)) * 60 + 500 + tab[i][j + 1]
					, (j + i) * 30 + 200, (j + i + 1) * 30 + 200, param, tab[i][j] != tab[i][j + 1] ? 0x66FFF : 0xFFFF);
			j += 1;
		}
	
		i += 1;
	}


	ft_printf("%d %d\n", tab[0][0], tab[1][0]);
	//	ligne(500 + tab[0][0], 440 + tab[0][1], 200, 230, param);
	//	ligne(440 + tab[0][1], 380 + tab[0][2], 200, 230, param);
	//	ligne(560, 500, 230, 260, param);
	//	trace_seg(500, 560, 260, 290, param);
	return (0);
}

int	main(int ac, char **av)
{
	char	**tab;
	char	*line;
	void	*init;
	void	*win;
	int		fd;
	void	*save[4];
	int		x;
	int		y;

	fd = open(av[1], O_RDONLY);
	init = mlx_init();
	x = -1;
	y = 0;

	win = mlx_new_window(init, 2048, 2048, "test");
	save[0] = init;
	save[1] = win;
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		if (!is_tab_ok(tab, x))
			return (0);
		x = get_tab_len(tab);
		y++;
	}
	do_stuff(x, y, av[1], save);
//	mlx_mouse_hook(win, get_mouse, save);
	mlx_loop(init);
}
