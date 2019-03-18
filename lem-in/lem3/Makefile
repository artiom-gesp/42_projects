CC			=	clang
NAME		=	lem-in
VISU		=	visu
FLAGS		=	-Wall -Wextra -Werror
LIBDIR		=	libft
LIBLINK		=	-L $(LIBDIR) -lft
LIB 		=	$(LIBDIR)/libft.a
LIB_VISU	=	-framework Opengl -framework AppKit

INCLUDES	= 	-I ./includes
INCLUDE		=	./includes
INCLUDES_VISU	=	-I ~/usr/local/includes/ 

OBJDIR		= 	objs

OBJDIR_ALGO	=	objs/algo
OBJDIR_VISU	=	objs/visual

SRCDIR_ALGO	=	srcs/algo
SRCDIR_VISU	=	srcs/visual

SRC_ALGO	=	main.c\
				parsing.c\
				add_info.c\
				add_ants.c\
				add_rooms.c\
				add_links.c\
				reader.c\
				created_map.c\
				created_hash.c\
				created_path.c\
				path_creation_utils.c\
				visu.c\
				design.c\
				event.c\
				image.c\
				view_map.c\
				
SRC_VISU	=	

OBJ_ALGO	=	$(SRC_ALGO:.c=.o)
OBJ_VISU	=	$(SRC_VISU:.c=.o)

SRCS_ALGO	=	$(addprefix $(SRCDIR_ALGO)/, $(SRC_ALGO))
OBJS_ALGO	=	$(addprefix $(OBJDIR_ALGO)/, $(SRC_ALGO:.c=.o))

SRCS_VISU	=	$(addprefix $(SRCDIR_VISU)/, $(SRC_VISU))
OBJS_VISU	=	$(addprefix $(OBJDIR_VISU)/, $(SRC_VISU:.c=.o))


all: directory $(NAME) $(VISU)

$(NAME): $(OBJDIR_ALGO) $(LIB) $(OBJS_ALGO) $(INCLUDE)
	@$(CC) $(FLAGS) srcs/algo/libmlx.a $(LIB) $(LIB_VISU)  -o $@ $(OBJS_ALGO) $(LIBLINK)

# $(VISU): $(OBJDIR_VISU) $(LIB) $(OBJS_VISU) $(INCLUDE)
# 	cc  $(LIB) $(LIB_VISU) -o $@ $(OBJS_VISU) 

$(LIB):
	@make -C $(LIBDIR)

$(OBJDIR_ALGO)/%.o: $(SRCDIR_ALGO)/%.c
	gcc $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(OBJDIR_VISU)/%.o: $(SRCDIR_VISU)/%.c
	gcc $(FLAGS) -c $^ -o $@ $(INCLUDES) $(INCLUDES_VISU)

directory: $(OBJDIR) $(OBJDIR_ALGO) $(OBJDIR_VISU)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR_ALGO):
	@mkdir -p $(OBJDIR_ALGO)

$(OBJDIR_VISU):
	@mkdir -p $(OBJDIR_VISU)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJS_ALGO)
	@make -C $(LIBDIR) clean
	@rm -rf $(OBJDIR_ALGO)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(VISU)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: clean all re fclean directory
