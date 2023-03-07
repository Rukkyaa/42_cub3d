# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 17:19:09 by axlamber          #+#    #+#              #
#    Updated: 2023/03/07 14:23:07 by axlamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLXFLAGS = -Lmlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

#################################################################################################
# $$\      $$\  $$$$$$\  $$\   $$\ $$$$$$$\   $$$$$$\ $$$$$$$$\  $$$$$$\  $$$$$$$\ $$\     $$\  #
# $$$\    $$$ |$$  __$$\ $$$\  $$ |$$  __$$\ $$  __$$\\__$$  __|$$  __$$\ $$  __$$\\$$\   $$  | #
# $$$$\  $$$$ |$$ /  $$ |$$$$\ $$ |$$ |  $$ |$$ /  $$ |  $$ |   $$ /  $$ |$$ |  $$ |\$$\ $$  /  #
# $$\$$\$$ $$ |$$$$$$$$ |$$ $$\$$ |$$ |  $$ |$$$$$$$$ |  $$ |   $$ |  $$ |$$$$$$$  | \$$$$  /   #
# $$ \$$$  $$ |$$  __$$ |$$ \$$$$ |$$ |  $$ |$$  __$$ |  $$ |   $$ |  $$ |$$  __$$<   \$$  /    #
# $$ |\$  /$$ |$$ |  $$ |$$ |\$$$ |$$ |  $$ |$$ |  $$ |  $$ |   $$ |  $$ |$$ |  $$ |   $$ |     #
# $$ | \_/ $$ |$$ |  $$ |$$ | \$$ |$$$$$$$  |$$ |  $$ |  $$ |    $$$$$$  |$$ |  $$ |   $$ |     #
# \__|     \__|\__|  \__|\__|  \__|\_______/ \__|  \__|  \__|    \______/ \__|  \__|   \__|     #
#################################################################################################
NAME = cub3d

SRC = mandatory/main.c mandatory/window_init.c mandatory/game_loop.c \
		mandatory/free.c mandatory/move.c \
		mandatory/raycast_2D.c \
		mandatory/render/load.c \
		mandatory/render/render_fps.c mandatory/render/color.c \
		mandatory/events.c \


OBJS = $(SRC:.c=.o)

# SHAPES FILES #
SHAPE_SRC = $(addprefix mandatory/shapes/, $(addsuffix .c, square circle line pixel_utils))
SHAPE_OBJS = $(SHAPE_SRC:.c=.o)

# MAP FILES #
MAP_SRC = $(addprefix mandatory/map/, $(addsuffix .c, get_map map_utils))
MAP_OBJS = $(MAP_SRC:.c=.o)

# VECTOR FILES #
VECTOR_SRC = $(addprefix mandatory/vector/vec_, $(addsuffix .c, angle distance mult normalize \
	print scalar_mult sum to_angle rotate_edit rotate))
VECTOR_OBJS = $(VECTOR_SRC:.c=.o)


INCLUDE = ./includes

HEADERS = ./includes/cub3d

#
#
# BONUS
#
#

NAME_BONUS = cub3d_bonus

SRC_BONUS = bonus/main.c bonus/window_init.c bonus/game_loop.c \
		bonus/free.c bonus/draw_player.c \
		bonus/raycast_2D.c \
		bonus/events.c \

OBJS_BONUS = $(SRC_BONUS:.c=.o)

# SHAPES FILES #
SHAPE_SRC_BONUS = $(addprefix bonus/shapes/, $(addsuffix .c, square circle line pixel_utils rectangle))
SHAPE_OBJS_BONUS = $(SHAPE_SRC_BONUS:.c=.o)

# MAP FILES# #
MAP_SRC_BONUS = $(addprefix bonus/map/, $(addsuffix .c, get_map map_utils))
MAP_OBJS_BONUS = $(MAP_SRC_BONUS:.c=.o)

# VECTOR FILES #
VECTOR_SRC_BONUS = $(addprefix bonus/vector/vec_, $(addsuffix .c, angle distance mult normalize \
	print scalar_mult sum to_angle rotate_edit rotate))
VECTOR_OBJS_BONUS = $(VECTOR_SRC_BONUS:.c=.o)

# SOUND FILES #
SOUND_SRC_BONUS = $(addprefix bonus/sound/, $(addsuffix .c, sound))
SOUND_OBJS_BONUS = $(SOUND_SRC_BONUS:.c=.o)

# RENDER #
RENDER_SRC_BONUS = $(addprefix bonus/render/, $(addsuffix .c, load render_fps pixel_ops wall))
RENDER_OBJS_BONUS = $(RENDER_SRC_BONUS:.c=.o)

# INVENTORY #
INVENTORY_SRC_BONUS = $(addprefix bonus/inventory/, $(addsuffix .c, utils))
INVENTORY_OBJS_BONUS = $(INVENTORY_SRC_BONUS:.c=.o)

# MINIAUDIO #
MINIAUDIO = bonus/sound/miniaudio.o

HEADERS_BONUS = ./includes/cub3d_bonus.h ./includes/miniaudio.h

LIBFT = -L libft/ -lft

flag:= 1
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
	@cc -Wall -Wextra -g3 -O3 -I $(INCLUDE) -I/usr/include -Imlx_linux -O3 -c $< -o ${<:.c=.o}
	$(eval flag=$(shell echo $$(($(flag)+1))))

all: $(NAME)

$(NAME): $(HEADERS) $(OBJS) $(SHAPE_OBJS) $(MAP_OBJS) $(VECTOR_OBJS)
	@printf "\033[K\033[1;32m| Cub3d : compiled                     |\n\033[m"
	@make --no-print-directory -C libft/
	@cc $(OBJS) $(SHAPE_OBJS) $(MAP_OBJS) $(VECTOR_OBJS) $(MLXFLAGS) $(LIBFT) -o $(NAME)
	@printf "\033[1;32m========================================\n"
	@printf "|         COMPILATION FINISHED !       |\n"
	@printf "========================================\n\033[m"
	@setterm -cursor on

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(HEADERS_BONUS) $(OBJS_BONUS) $(SHAPE_OBJS_BONUS) $(MAP_OBJS_BONUS) $(VECTOR_OBJS_BONUS) $(SOUND_OBJS_BONUS) $(RENDER_OBJS_BONUS) $(INVENTORY_OBJS_BONUS)
	@printf "\033[K\033[1;32m| Cub3d bonus: compiled                |\n\033[m"
	@make --no-print-directory -C libft/
	@cc $(OBJS_BONUS) -O3 $(SHAPE_OBJS_BONUS) $(MAP_OBJS_BONUS) $(VECTOR_OBJS_BONUS) $(SOUND_OBJS_BONUS) $(RENDER_OBJS_BONUS) $(INVENTORY_OBJS_BONUS) $(MINIAUDIO) $(MLXFLAGS) -lpthread -ldl $(LIBFT) -o $(NAME_BONUS)
	@printf "\033[1;32m========================================\n"
	@printf "|            BONUS FINISHED !          |\n"
	@printf "========================================\n\033[m"
	@setterm -cursor on

perf: fclean $(HEADERS_BONUS) $(OBJS_BONUS) $(SHAPE_OBJS_BONUS) $(MAP_OBJS_BONUS) $(VECTOR_OBJS_BONUS) $(SOUND_OBJS_BONUS) $(RENDER_OBJS_BONUS) $(INVENTORY_OBJS_BONUS)
	@printf "\033[K\033[1;32m| Cub3d bonus perf: compiled           |\n\033[m"
	@make --no-print-directory -C libft/
	@cc $(OBJS_BONUS) $(SHAPE_OBJS_BONUS) $(MAP_OBJS_BONUS) $(VECTOR_OBJS_BONUS) $(SOUND_OBJS_BONUS) $(RENDER_OBJS_BONUS) $(INVENTORY_OBJS_BONUS) $(MINIAUDIO) $(MLXFLAGS) -pg -lpthread -ldl $(LIBFT) -o $(NAME_BONUS)
	@printf "\033[1;32m========================================\n"
	@printf "|            PERF FINISHED !           |\n"
	@printf "========================================\n\033[m"
	@setterm -cursor on
	@./cub3d_bonus maps/map.cub
	@gprof cub3d_bonus gmon.out > analysis.txt
	@rm gmon.out

clean:
	@printf "\033[1;31m========================================\n"
	@printf "|            CUB3D CLEANING            |\n"
	@printf "========================================\n\033[m"
	@printf "\033[K\033[1;31m|\033[1;33m Destroying objects                   \033[1;31m|\n\033[m"
	@make --no-print-directory clean -C libft/
	@rm -f $(OBJS) $(SHAPE_OBJS) $(MAP_OBJS) $(VECTOR_OBJS)
	@rm -f $(OBJS_BONUS) $(SHAPE_OBJS_BONUS) $(MAP_OBJS_BONUS) $(VECTOR_OBJS_BONUS) $(SOUND_OBJS_BONUS) $(RENDER_OBJS_BONUS) $(INVENTORY_OBJS_BONUS)
	@printf "\033[1;31m========================================\n\033[m"

fclean: clean
	@printf "\033[K\033[1;31m|\033[1;31m Destroying all                       \033[1;31m|\n\033[m"
	@make --no-print-directory fclean -C libft/
	@rm -f $(NAME) $(NAME_BONUS)
	@printf "\033[1;31m========================================\n\033[m"

re: fclean all

.PHONY: all clean fclean re
