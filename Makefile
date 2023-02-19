# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: theo <theo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 17:19:09 by axlamber          #+#    #+#              #
#    Updated: 2023/02/18 14:32:21 by theo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = mandatory/main.c mandatory/window_init.c mandatory/get_map.c mandatory/key.c \
		mandatory/free.c mandatory/move.c mandatory/vector_ops.c \
		mandatory/raycast_2D.c \
		mandatory/render/load.c \
		mandatory/render/render_fps.c

LFLAGS = -Lmlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

OBJS = $(SRC:.c=.o)

# SHAPES FILES #
SHAPE_SRC = $(addprefix mandatory/shapes/, $(addsuffix .c, square circle line))
SHAPE_OBJS = $(SHAPE_SRC:.c=.o)

LFLAGS = -Lmlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

INCLUDE = ./includes

LIBFT = -L libft/ -lft

.c.o :
	@setterm -cursor off
	@if [ $(flag) = "1" ]; then\
		clear ;\
		printf "\033[1;35m========================================\n";\
		printf "|           CUB3D LOADING....          |\n";\
		printf "========================================\n";\
	fi
	@printf "\033[1;32m|\033[32m                                       \033[m\r"
	@printf "\033[1;35m|\033[0;32m Compiling $@... \033[m\r"
	@cc -Wall -Wextra -g -I $(INCLUDE) -I/usr/include -Imlx_linux -O3 -c $< -o ${<:.c=.o}
	$(eval flag=$(shell echo $$(($(flag)+1))))

all: $(NAME)

$(NAME): $(OBJS) $(SHAPE_OBJS)
	@printf "\033[K\033[1;32m| Cub3d : compiled                     |\n\033[m"
	@make --no-print-directory -C libft/
	@cc $(OBJS) $(SHAPE_OBJS) $(LFLAGS) $(LIBFT) -o $(NAME)
	@printf "\033[1;32m========================================\n"
	@printf "|         COMPILATION FINISHED !       |\n"
	@printf "========================================\n\033[m"
	@setterm -cursor on

debug: $(LIBS) clean
	$(CC) $(SRC) $(LIBS) $(HEADERS) $(LFLAGS) -g3 -O3 -o $(NAME) 

clean:
	@printf "\033[1;31m========================================\n"
	@printf "|            CUB3D CLEANING            |\n"
	@printf "========================================\n\033[m"
	@printf "\033[K\033[1;31m|\033[1;33m Destroying objects                   \033[1;31m|\n\033[m"
	@make --no-print-directory clean -C libft/
	@rm -f $(OBJS) $(OBJS_BONUS) $(SHAPE_OBJS)
	@printf "\033[1;31m========================================\n\033[m"

fclean: clean
	@printf "\033[K\033[1;31m|\033[1;31m Destroying all                       \033[1;31m|\n\033[m"
	@make --no-print-directory fclean -C libft/
	@rm -f $(NAME)
	@printf "\033[1;31m========================================\n\033[m"

re: fclean all

.PHONY: all clean fclean re
