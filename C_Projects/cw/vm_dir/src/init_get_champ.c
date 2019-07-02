/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:32:23 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/20 15:40:21 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <limits.h>

static void	*return_error(char *err, char *arg)
{
	if (arg)
		ft_dprintf(2, "corewar: %s %s\n", err, arg);
	else
		ft_dprintf(2, "corewar: %s\n", err);
	return (NULL);
}

t_champ		*new_champ(char *arg, int fd, int player_nb)
{
	t_champ		*champ;
	uint32_t	magic_number;

	if (read(fd, &magic_number, sizeof(uint32_t)) != sizeof(uint32_t))
		return (return_error("could not read file", arg));
	if (ft_swap_int32(magic_number) != COREWAR_EXEC_MAGIC)
		return (return_error("invalid magic number for", arg));
	if (!(champ = ft_memalloc(sizeof(t_champ))))
		return (return_error("allocation error", NULL));
	if (read(fd, champ, T_CHAMP_SIZE) <= 0)
		return (return_error("could not read file", arg));
	if ((champ->size = ft_swap_int32(champ->size)) !=
		lseek(fd, 0, SEEK_END) - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16))
		return (return_error(arg, "has been corrupted"));
	if (champ->size > CHAMP_MAX_SIZE)
		return (return_error(arg, "is too fat"));
	champ->next = NULL;
	champ->player = player_nb;
	return (champ);
}

static int	get_player_nb(t_vm *vm, int player_nb)
{
	int			n;
	t_champ		*tmp;

	n = 1;
	tmp = vm->champs;
	while (tmp)
	{
		if (tmp->player == n && !player_nb)
		{
			++n;
			tmp = vm->champs;
		}
		else if (player_nb && tmp->player == player_nb)
		{
			return (-1);
		}
		else
			tmp = tmp->next;
	}
	return (player_nb > 0 ? player_nb : n);
}

static void	add_champ(t_vm *vm, t_champ *champ)
{
	t_champ	*tmp;
	t_champ	*prev;

	if (!(tmp = vm->champs))
	{
		vm->champs = champ;
		return ;
	}
	while (tmp && tmp->player > champ->player)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == vm->champs)
	{
		champ->next = tmp;
		vm->champs = champ;
	}
	else if (tmp)
	{
		prev->next = champ;
		champ->next = tmp;
	}
	else
		prev->next = champ;
}

int			get_champ(char *arg, t_vm *vm, int *player_nb)
{
	int			fd;
	t_champ		*champ;

	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		ft_dprintf(2, "corewar: Failed to open %s\n", arg);
		return (0);
	}
	if ((*player_nb = get_player_nb(vm, *player_nb)) < 0)
	{
		ft_dprintf(2, "corewar: Invalid player number\n");
		close(fd);
		return (0);
	}
	if (!(champ = new_champ(arg, fd, *player_nb)))
	{
		close(fd);
		return (0);
	}
	close(fd);
	add_champ(vm, champ);
	++vm->nb_players;
	*player_nb = 0;
	return (1);
}
