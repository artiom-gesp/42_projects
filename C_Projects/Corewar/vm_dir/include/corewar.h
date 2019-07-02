/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:24:59 by pfragnou          #+#    #+#             */
/*   Updated: 2019/06/20 15:42:08 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdint.h>
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include "viewer.h"

# define REG_OFFSET		1
# define IND_OFFSET		2
# define DIR_OFFSET		4

# define OPT_VIEWER		1
# define OPT_DEBUG  	2
# define OPT_HELP		4
# define OPT_DUMP		8
# define OPT_N			16
# define OPT_DESC		32

# define C_CURR			0
# define C_TOTAL		1
# define C_DIE			2

# define T_CHAMP_SIZE	PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 12

typedef struct		s_champ
{
	uint8_t				name[PROG_NAME_LENGTH];
	int					name_pad;
	int					size;
	uint8_t				comment[COMMENT_LENGTH];
	int					comment_pad;
	uint8_t				code[CHAMP_MAX_SIZE];
	int					player;
	uint8_t				play_pos;
	int					pc;
	int					nb_lives;
	int					nb_procs;
	struct s_champ		*next;
}					t_champ;

typedef struct		s_data
{
	uint32_t			args[3];
	uint8_t				typecode;
	int					pc;
	struct s_op			*op;
}					t_data;

typedef struct		s_proc
{
	int32_t				r[REG_NUMBER];
	int					pc;
	int					last_pc;
	int					last_color;
	uint8_t				carry;
	uint8_t				player;
	int					lives;
	int					sleep;
	int					pos;
	t_data				d;
	struct s_proc		*next;
}					t_proc;

typedef struct		s_vm
{
	int					opt;
	int					nb_players;
	int					last_alive;
	t_proc				*proc;
	int					nb_procs;
	uint8_t				mem[MEM_SIZE];
	int					dump;
	t_champ				*champs;
	t_viewer			*vw;
}					t_vm;

typedef int			(*t_inst)(t_vm*, t_proc*, t_data*);

typedef struct		s_op
{
	char				*name;
	int					nb_arg;
	int					allowed_types[3];
	int					opcode;
	int					sleep;
	char				*description;
	int					encoded_type;
	int					alt_dir_size;
	t_inst				func;
	int					mod;
}					t_op;

t_op				g_optab[17];

/*
** init
*/

int					parse_input(int argc, char **argv, t_vm *vm);
int					init_vm(t_vm *vm, char *path);
int					get_champ(char *arg, t_vm *vm, int *player_nb);

/*
** instruction handling / main vm loop
*/

int					handle_inst(t_vm *vm, t_proc *p, t_op *op);
int					periodic_check(t_vm *vm, int cycle_to_die);
int					get_args(t_vm *vm, t_proc *p, t_op *op);
void				exec_vm(t_vm *vm);

/*
** instructions
*/

int					live_32(t_vm *vm, t_proc *p, t_data *d);
int					ld_32(t_vm *vm, t_proc *p, t_data *d);
int					st_32(t_vm *vm, t_proc *p, t_data *d);
int					add_32(t_vm *vm, t_proc *p, t_data *d);
int					sub_32(t_vm *vm, t_proc *p, t_data *d);
int					and_32(t_vm *vm, t_proc *p, t_data *d);
int					or_32(t_vm *vm, t_proc *p, t_data *d);
int					xor_32(t_vm *vm, t_proc *p, t_data *d);
int					zjmp_32(t_vm *vm, t_proc *p, t_data *d);
int					ldi_32(t_vm *vm, t_proc *p, t_data *d);
int					sti_32(t_vm *vm, t_proc *p, t_data *d);
int					fork_32(t_vm *vm, t_proc *p, t_data *d);
int					lld_32(t_vm *vm, t_proc *p, t_data *d);
int					lldi_32(t_vm *vm, t_proc *p, t_data *d);
int					lfork_32(t_vm *vm, t_proc *p, t_data *d);
int					aff_32(t_vm *vm, t_proc *p, t_data *d);

/*
** viewer
*/

void				init_arena_viewer(WINDOW *win, t_champ *ch);
void				init_info_viewer(WINDOW *win, t_champ *ch);
void				update_info(t_vm *vm, int *cycles);
int					update_viewer(t_vm *vm, int *cycles);
void				display_winner(t_vm *vm);
void				update_pc(WINDOW *win, t_proc *p);
void				viewer_aff(WINDOW *win, char c, int player);

/*
** tools
*/

void				kill_proc(t_vm *vm, t_proc *cur, t_proc *prev);
t_proc				*new_proc(t_vm *vm, t_proc p);
int16_t				read_16(void *data, int idx);
uint32_t			read_32(void *data, int idx);
void				write_32(uint32_t data, t_vm *vm, int idx, int player);

void				print_operations(t_vm *vm, t_proc *p, int pc);
void				dump_vm(t_vm *vm, int octet_per_line);
int					g_int_par(char **arg);
void				get_winner(t_vm *vm);
#endif
