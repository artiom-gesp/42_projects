/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 02:26:05 by amanuel           #+#    #+#             */
/*   Updated: 2019/06/29 23:27:18 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void			ft_file_location(t_asm *s, char *av)
{
	int		i;

	i = 0;
	if (ft_strchr(av, '/'))
	{
		ft_printf("We detected that the champion.s is in a remote directory,");
		ft_printf("\nwould you like to get .cor in the current directory");
		ft_printf(" [Y/n]\n");
		if (get_next_line(1, &s->line) > 0)
		{
			if (s->line && (!*s->line || *s->line == 'y' || *s->line == 'Y'))
				while (ft_strchr(av + i, '/'))
					i += 1 + ft_strchr(av + i, '/') - (av + i);
			ft_memdel((void**)&s->line);
		}
	}
	s->fresh = ft_strndup(av + i, s->file_name_size - i - 2);
	s->fresh = ft_strjoin_free(s->fresh, ".cor", 1);
	ft_printf("Writing output program to %s\n", s->fresh);
	s->fd = open(s->fresh, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(s->fresh);
}
