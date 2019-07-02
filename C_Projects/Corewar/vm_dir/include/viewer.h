/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:31:21 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/23 20:31:22 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H
# include <ncurses.h>
# include <limits.h>
# include <stdint.h>

# define BPL			64
# define MEM_H			(BPL + 2)
# define MEM_W			(BPL * 3 + 1)
# define MEM_X			2
# define MEM_Y			1
# define BG_W			260
# define BG_H			(MEM_H + 2)
# define BG_X			0
# define BG_Y			0
# define INFO_H			MEM_H
# define INFO_W			(BG_W - MEM_W - MEM_X - 1)
# define INFO_X			(BG_W - INFO_W - 1)
# define INFO_Y			MEM_Y
# define INFO_OFFSET	3
# define LIVE_OFFSET	INFO_OFFSET + 8
# define STAT_OFFSET	20
# define CONTROL_OFFSET	STAT_OFFSET + 8
# define COLUMN_OFFSET	INFO_OFFSET + 16
# define WIN_OFFSET		CONTROL_OFFSET + 10

# define STATUS_PAUSE 	1
# define STATUS_RUN 	0

# define DEF_COLOR		5

# define CONTROL_QUIT	'q'
# define CONTROL_PAUSE	' '
# define CONTROL_FAST	'3'
# define CONTROL_MEDIUM	'2'
# define CONTROL_SLOW	'1'
# define CONTROL_SLOWER	'e'
# define CONTROL_FASTER	'd'
# define SPLASH_FILE	"ressources/splash.txt"

typedef struct			s_viewer
{
	WINDOW				*background;
	WINDOW				*mem_win;
	WINDOW				*info_win;
	int					status;
	int					delay;
}						t_viewer;

/*
** print a byte in the memory window
*/

void					wprintmem(WINDOW *win, uint8_t val, int pc);
void					wprintmemc(WINDOW *win, uint8_t val, int pc, int color);
void					wprintmemc_32(WINDOW *win, uint32_t val, int pc,
	int player);
WINDOW					*new_window(int x[4], int border, char *title);

/*
** Initialization
*/

int						exit_viewer(t_viewer *vw, int exit_status, char *msg);
t_viewer				*init_viewer(char *path);
int						viewer_splash(char *path);

/*
** controls
*/

int						viewer_pause(t_viewer *vw);
int						viewer_control(t_viewer *vw);

#endif
