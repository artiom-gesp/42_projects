# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanuel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/24 01:22:10 by amanuel           #+#    #+#              #
#    Updated: 2019/06/01 16:33:09 by amanuel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_DIR	= asm_dir
VM_DIR	= vm_dir

all:	corewar asm

corewar:
	@$(MAKE) -C $(VM_DIR)

asm:
	@$(MAKE) -C $(ASM_DIR)

clean:
	@$(MAKE) clean -C $(ASM_DIR)
	@$(MAKE) clean -C $(VM_DIR)

fclean:
	@$(MAKE) fclean -C $(ASM_DIR)
	@$(MAKE) fclean -C $(VM_DIR)

re: fclean all

.PHONY: all clean fclean re corewar asm
