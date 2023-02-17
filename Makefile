# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teliet <teliet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 17:19:09 by axlamber          #+#    #+#              #
#    Updated: 2023/02/16 17:30:21 by teliet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = mandatory/main.c mandatory/window_init.c mandatory/get_map.c mandatory/key.c \
		mandatory/free.c mandatory/move.c

CC = gcc

HEADERS = -I ./includes

LFLAGS = -Lmlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

LIBS =  -L libft/ -lft

OBJ = $(SRC:.c=.o)

all: ${NAME}
 
$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) $(LIBS) $(HEADERS) $(LFLAGS) -o $(NAME)

	
debug: clean
	$(CC) $(SRC) $(LIBS) $(HEADERS) $(LFLAGS) -g3 -O3 -o $(NAME) 

%.o: %.c
	$(CC) -Wall -Wextra -Werror $(HEADERS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f ${NAME}

re: fclean all
