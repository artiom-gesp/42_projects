/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_get_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:26:04 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/23 20:26:05 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	return_error(char *err, char *arg, char c)
{
	if (arg)
		ft_dprintf(2, "corewar: %s %s\n", err, arg);
	else if (c)
		ft_dprintf(2, "corewar: %s %c\n", err, c);
	return (0);
}

static int	get_long_opt(char *arg, int *opt)
{
	int		i;
	char	opt_table[4][7];

	ft_strcpy(opt_table[0], "viewer");
	ft_strcpy(opt_table[1], "debug");
	ft_strcpy(opt_table[2], "help");
	ft_strcpy(opt_table[3], "dump");
	i = 0;
	while (i < 4 && ft_strcmp(opt_table[i], arg))
		++i;
	if (i < 4)
		*opt |= 1 << i;
	else
		return (return_error("invalid option", arg, 0));
	return (1);
}

static int	get_opt(char *arg, int *opt)
{
	char	c;

	while (*arg)
	{
		if ((c = ft_findchar("vghdnc", *arg)) >= 0)
			*opt |= (1 << c);
		else if (*arg == '-')
			return (get_long_opt(arg + 1, opt));
		else
			return (return_error("invalid option", NULL, *arg));
		++arg;
	}
	return (1);
}

static int	get_int(char *str, int *ret)
{
	long long	result;
	int			len;
	int			sign;

	len = 0;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	sign = (*str == '+' || *str == '-') ? -(*str++ - 44) : 1;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str++ - '0');
		++len;
	}
	result *= sign;
	if (len > 11 || result < 0 || result > INT_MAX
		|| (*str && *str != ' ' && *str > 13))
		return (0);
	*ret = result;
	return (1);
}

int			parse_input(int argc, char **argv, t_vm *vm)
{
	int			i;
	int			player_nb;

	i = 0;
	player_nb = 0;
	while (++i < argc)
	{
		if (vm->opt & OPT_DUMP || vm->opt & OPT_N)
		{
			if (!(get_int(argv[i], vm->opt & OPT_N ? &player_nb : &vm->dump)))
				return (return_error("invalid argument", argv[i], 0));
			vm->opt &= ~(OPT_DUMP | OPT_N);
		}
		else if (*argv[i] == '-' && player_nb == 0)
		{
			if (!(get_opt(argv[i] + 1, &vm->opt)))
				return (0);
		}
		else if (!(get_champ(argv[i], vm, &player_nb)))
			return (0);
	}
	if ((vm->opt & (OPT_VIEWER | OPT_DEBUG)) == (OPT_VIEWER | OPT_DEBUG))
		vm->opt &= ~OPT_DEBUG;
	return (1);
}
