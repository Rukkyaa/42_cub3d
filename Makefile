# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teliet <teliet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 17:19:09 by axlamber          #+#    #+#              #
#    Updated: 2023/02/17 14:48:37 by teliet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = mandatory/main.c mandatory/window_init.c mandatory/get_map.c mandatory/key.c \
		mandatory/free.c mandatory/move.c mandatory/shapes.c mandatory/vector_ops.c \
		mandatory/raycast_2D.c


LFLAGS = -Lmlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

OBJS = $(SRC:.c=.o)

INCLUDE = includes/

LIBFT = -L libft/ -lft

.c.o :
	cc -Wall -Wextra -g -I/usr/include -Imlx_linux -O3 -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@make --no-print-directory -C libft/
	@cc $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME)

debug: $(LIBS) clean
	$(CC) $(SRC) $(LIBS) $(HEADERS) $(LFLAGS) -g3 -O3 -o $(NAME) 

clean:
	@make --no-print-directory clean -C libft/
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@make --no-print-directory fclean -C libft/
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
