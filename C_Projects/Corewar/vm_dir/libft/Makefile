# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanuel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 17:13:20 by tmanuel           #+#    #+#              #
#    Updated: 2018/12/27 16:18:20 by amanuel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binary

NAME = libft.a



# Path

SRC_PATH = ./src/

OBJ_PATH = ./objs/

INC_PATH = ./include/



# Name

SRC_NAME =	ft_atoi.c				\
			ft_count_whitespace.c	\
			ft_lstaddnew_free.c		\
			ft_memalloc.c			\
			ft_memset.c				\
			ft_strcmp.c				\
			ft_strdup.c				\
			ft_strjoin_f.c			\
			ft_strlen.c				\
			ft_strndup.c			\
			ft_strtab.c				\
			ft_swap_bytes.c			\
			ft_findchar.c			\
			ft_strcpy.c
	
OBJ_NAME = $(SRC_NAME:.c=.o)



# Files

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))



# Flags

FLAGS = -Wall -Wextra -Werror



# Display

ifndef ECHO
	T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
		-nrRf $(firstword $(MAKEFILE_LIST)) \
		ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
	N := x
	C = $(words $N)$(eval N := x $N)
	ECHO = printf "\r[`expr $C '*' 100 / $T`%%]"
endif



# Rules

all: $(NAME)

$(NAME): $(OBJ) 
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\rLibcorewar done                    \n"
	@tput cvvis

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@tput civis
	@gcc $(FLAGS) -I$(INC_PATH) -o $@ -c $<
	@tput setaf 10
	@$(ECHO)
	@echo -n $@
	@printf "                              "

clean:
	@rm -rf $(OBJ_PATH)
	@tput setaf 9
	@echo "Libft clean"

fclean: 
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@tput setaf 9
	@echo "Libcorewar fclean"

re:
	@make fclean && make

.PHONY: all clean fclean re
