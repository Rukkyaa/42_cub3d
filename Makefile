# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teliet <teliet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 17:19:09 by axlamber          #+#    #+#              #
#    Updated: 2023/02/17 10:42:28 by teliet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = mandatory/main.c mandatory/window_init.c mandatory/get_map.c mandatory/key.c \
		mandatory/free.c mandatory/move.c mandatory/shapes.c


OBJS = $(SRC:.c=.o)

INCLUDE = includes/

LIBFT = -L libft/ -lft

.c.o :
	cc -Wall -Wextra -I/usr/include -Imlx_linux -O3 -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@make --no-print-directory -C libft/
	@cc $(OBJS) mlx/libmlx.a mlx/libmlx_Linux.a -L. -lXext -L. -lX11 $(LIBFT) -o $(NAME)

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