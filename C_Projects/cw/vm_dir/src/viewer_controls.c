/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:26:43 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/16 18:26:44 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

int		viewer_pause(t_viewer *vw)
{
	vw->status = STATUS_PAUSE;
	mvwprintw(vw->info_win, STAT_OFFSET + 3, COLUMN_OFFSET, "paused ");
	wrefresh(vw->info_win);
	while (vw->status == STATUS_PAUSE)
	{
		if (viewer_control(vw) == 0)
			return (0);
	}
	mvwprintw(vw->info_win, STAT_OFFSET + 3, COLUMN_OFFSET, "running");
	return (1);
}

int		viewer_control(t_viewer *vw)
{
	char	c;

	if ((c = getch()) == CONTROL_QUIT)
		return (0);
	else if (c == CONTROL_PAUSE)
	{
		if (vw->status == STATUS_PAUSE)
			vw->status = STATUS_RUN;
		else
			return (viewer_pause(vw));
	}
	else if (c == CONTROL_FAST)
		vw->delay = 0;
	else if (c == CONTROL_MEDIUM)
		vw->delay = 2500;
	else if (c == CONTROL_SLOW)
		vw->delay = 10000;
	else if (c == CONTROL_FASTER)
		vw->delay = vw->delay > 50 ? vw->delay - 20 : 0;
	else if (c == CONTROL_SLOWER)
		vw->delay += 50;
	mvwprintw(vw->info_win, STAT_OFFSET + 4, COLUMN_OFFSET, "%dms\t\t",
		vw->delay);
	wrefresh(vw->info_win);
	return (1);
}
