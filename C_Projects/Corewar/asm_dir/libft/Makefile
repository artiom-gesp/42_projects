# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanuel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 17:13:20 by tmanuel           #+#    #+#              #
#    Updated: 2019/06/01 16:29:46 by amanuel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binary

NAME = libft.a



# Path

SRC_PATH = srcs/

OBJ_PATH = objs/

INC_PATH = includes/



# Name

SRC_NAME =	ft_atoi.c \
		ft_atol.c \
		ft_itoa.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_memset.c \
		ft_pow.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_strjoin_free.c \
		ft_strlen.c \
		ft_strndel.c \
		ft_strndup.c \
		ft_strnew.c \
		ft_strnjoin_free.c \
		ft_tabnew.c \
		get_next_line.c \
		ft_findc.c \
		ft_printf_part_1.c \
		ft_printf_part_2.c \
		ft_ltoa.c \
		ft_uitoa_base.c \
		ft_ultoa_base.c \
		ft_itostr.c \
		ft_strset.c \
		ft_lilstr.c \
		ft_strins_free.c \
		ft_freetab.c \
		ft_tablen.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_addarray.c \
		ft_isint.c \
		ft_puttab.c \
		ft_putvoid_fd.c \
		ft_reverse_int.c \
		ft_strncpy.c \
		ft_count_whitespace.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_lstaddnew.c \
		ft_strtab.c \
	
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
	@printf "\rLibasm done                    \n"
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
	@echo "Libasm clean"

fclean: 
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@tput setaf 9
	@echo "Libasm fclean"

re:
	@make fclean && make

.PHONY: all clean fclean re
