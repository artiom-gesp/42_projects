CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

NAME		=	../corewar

SRC_DIR		=	./src

SRC			=	$(addprefix $(SRC_DIR)/,$(SRCS))

SRCS		=	corewar.c					\
				init_get_input.c			\
				init_get_champ.c			\
				init.c						\
				tools.c						\
				op.c						\
				debug.c						\
				result_print.c 				\
				exec_vm.c					\
				exec_get_args.c				\
				exec_checks.c				\
				exec_inst_handler.c			\
				inst_spe.c					\
				inst_load.c 				\
				inst_store.c 				\
				inst_math.c 				\
				viewer.c					\
				viewer_info.c				\
				viewer_init.c				\
				viewer_tools.c				\
				viewer_controls.c			\
				viewer_splash.c

OBJ_DIR		=	./obj

OBJ			=	$(addprefix $(OBJ_DIR)/,$(OBJS))
OBJS		=	$(SRCS:.c=.o)

INC_DIR		=	./include
INC			=	$(INC_DIR)/corewar.h $(INC_DIR)/op.h $(INC_DIR)/viewer.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBFT_INC	=	$(LIBFT_DIR)/include

FTPF_DIR	=	./ft_printf
FTPF		=	$(FTPF_DIR)/libftprintf.a
FTPF_INC	=	$(FTPF_DIR)/include

INC_FLAGS	=	-I$(INC_DIR) -I$(LIBFT_INC) -I$(FTPF_INC)
LINK_FLAGS	=	-L$(LIBFT_DIR) -lft -L$(FTPF_DIR) -lftprintf -lncurses

# Display

ifndef ECHO
	T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
		-nrRf $(firstword $(MAKEFILE_LIST)) \
		ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
	N := x
	C = $(words $N)$(eval N := x $N)
	ECHO = printf "\r[`expr $C '*' 100 / $T`%%]"
endif


all:			$(NAME)

$(NAME):		$(OBJ_DIR) $(OBJ) $(LIBFT) $(FTPF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LINK_FLAGS)
	@printf "\rcorewar done                \n"
	@tput cvvis

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)
	@tput civis
	@tput setaf 10
	@$(ECHO)
	@echo -n $@
	@printf "                              "

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(FTPF):
	@$(MAKE) -C $(FTPF_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(FTPF_DIR) clean
	@rm -rf $(OBJ_DIR)
	@tput setaf 9
	@echo "corewar clean"

fclean:
	@$(MAKE) clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(FTPF_DIR) fclean
	@rm -f $(NAME)
	@tput setaf 9
	@echo "corewar fclean"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY:			all clean fclean re
