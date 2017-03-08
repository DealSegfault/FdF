# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhalit <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/27 22:03:25 by mhalit            #+#    #+#              #
#    Updated: 2017/02/24 20:31:14 by mhalit           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fdf.c\
	line.c
OBJ = fdf.o\
	line.o

LIBS = libft/libft.a\

NAME = fdf

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):

#recompiler les new .c
	make -C ./libft
	make -C ./minilibx_macos
	gcc $(FLAGS) -c $(SRCS)
	gcc $(FLAGS) $(OBJ) $(LIBS) -o $(NAME) -framework OpenGL -framework AppKit -I minilibx_macos ./minilibx_macos/libmlx.a
clean:
	rm -f $(OBJ)
	make -C ./libft clean
	make -C ./minilibx_macos clean
fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean
re: fclean all
