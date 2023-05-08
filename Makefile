# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 17:19:09 by axlamber          #+#    #+#              #
#    Updated: 2023/05/08 17:32:32 by axlamber         ###   ########.fr        #
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
		mandatory/render/load.c mandatory/render/render.c\
		mandatory/render/render_fps.c mandatory/render/color.c \
		mandatory/events.c \
		mandatory/garbage/free_garbage.c mandatory/garbage/gc_utils.c mandatory/garbage/singletons.c \
		mandatory/parsing/get_colors.c mandatory/parsing/get_next_line_utils.c mandatory/parsing/get_next_line.c \
		mandatory/parsing/get_texture.c mandatory/parsing/map_utils.c mandatory/parsing/map.c \
		mandatory/parsing/parse_map.c mandatory/parsing/parsing.c


OBJS = $(SRC:.c=.o)

# SHAPES FILES #
SHAPE_SRC = $(addprefix mandatory/shapes/, $(addsuffix .c, circle line pixel_utils))
SHAPE_OBJS = $(SHAPE_SRC:.c=.o)

# MAP FILES #
MAP_SRC = $(addprefix mandatory/map/, $(addsuffix .c, get_map map_utils))
MAP_OBJS = $(MAP_SRC:.c=.o)

# VECTOR FILES #
VECTOR_SRC = $(addprefix mandatory/vector/vec_, $(addsuffix .c, angle distance mult normalize \
	print scalar_mult sum to_angle rotate_edit rotate))
VECTOR_OBJS = $(VECTOR_SRC:.c=.o)


INCLUDE = ./includes

HEADERS = ./includes/cub3d.h

#
#
# BONUS
#
#

NAME_BONUS = cub3d_bonus

SRC_BONUS = bonus/main.c bonus/game_loop.c bonus/menu.c \
		bonus/free.c \
		bonus/raycast_2D.c bonus/raycast_2D_two.c

OBJS_BONUS = $(SRC_BONUS:.c=.o)

# SHAPES FILES #
SHAPE_SRC_BONUS = $(addprefix bonus/shapes/, $(addsuffix .c, square circle line pixel_utils rectangle))
SHAPE_OBJS_BONUS = $(SHAPE_SRC_BONUS:.c=.o)

# MAP FILES# #
MAP_SRC_BONUS = $(addprefix bonus/map/, $(addsuffix .c, get_map map_utils))
MAP_OBJS_BONUS = $(MAP_SRC_BONUS:.c=.o)

# VECTOR FILES #
VECTOR_SRC_BONUS = $(addprefix bonus/vector/vec_, $(addsuffix .c, angle distance mult normalize \
	print scalar_mult sum to_angle rotate_edit rotate rotate_rad copy resize zero))
VECTOR_OBJS_BONUS = $(VECTOR_SRC_BONUS:.c=.o)

# SOUND FILES #
SOUND_SRC_BONUS = $(addprefix bonus/sound/, $(addsuffix .c, sound game_sound load_sounds))
SOUND_OBJS_BONUS = $(SOUND_SRC_BONUS:.c=.o) 

# RENDER #
RENDER_SRC_BONUS = $(addprefix bonus/render/, $(addsuffix .c, quick_sort load render_fps multi_threading \
	precompute render_roof render_floor pixel_ops pixel_ops_fx wall sprites put_img_to_img debug_map color_ops \
	color_converts psychedelic_view render sort_imgs animation kill_counter))
RENDER_OBJS_BONUS = $(RENDER_SRC_BONUS:.c=.o)

# INVENTORY #
INVENTORY_SRC_BONUS = $(addprefix bonus/inventory/, $(addsuffix .c, utils utils2 refresh weapons))
INVENTORY_OBJS_BONUS = $(INVENTORY_SRC_BONUS:.c=.o)

# SINGLETONS #
SINGLETONS_SRC_BONUS = $(addprefix bonus/singletons/, $(addsuffix .c, singleton))
SINGLETONS_OBJS_BONUS = $(SINGLETONS_SRC_BONUS:.c=.o)

# GAME #
GAME_SRC_BONUS = $(addprefix bonus/game/, $(addsuffix .c, utils time player_move player_rotate player_collisions player_doors weapon weapon_utils))
GAME_OBJS_BONUS = $(GAME_SRC_BONUS:.c=.o)

# WAVES #
WAVE_SRC_BONUS = $(addprefix bonus/game/waves/, $(addsuffix .c, get_wave wave_utils))
WAVE_OBJS_BONUS = $(WAVE_SRC_BONUS:.c=.o)

# EVENTS #
EVENTS_SRC_BONUS = $(addprefix bonus/events/, $(addsuffix .c, hooks mouse_events key_events))
EVENTS_OBJS_BONUS = $(EVENTS_SRC_BONUS:.c=.o)

# SPRITES #
SPRITES_SRC_BONUS = $(addprefix bonus/sprites/, $(addsuffix .c, sprite_states spawn_zombie spawn_blood sprite_add_back sprite_add_front sprite_last new_item spawn_projectile\
	remove_entity move_sprite sprite_attack use_items zombie_stats collisions))
SPRITES_OBJS_BONUS = $(SPRITES_SRC_BONUS:.c=.o)

# INIT #
INIT_SRC_BONUS = $(addprefix bonus/init/, $(addsuffix .c, init init_player init_weapons init_windows\
	init_camera init_multi_threading basic_vectors sound load_sprites load_images load_images_2 create_img))
INIT_OBJS_BONUS = $(INIT_SRC_BONUS:.c=.o)

# GARBAGE #
GARBAGE_SRC_BONUS = $(addprefix bonus/garbage/, $(addsuffix .c, gc_utils free_garbage))
GARBAGE_OBJS_BONUS = $(GARBAGE_SRC_BONUS:.c=.o)

PARSING_SRC_BONUS = $(addprefix bonus/parsing/, $(addsuffix .c, get_colors get_next_line get_next_line_utils \
	get_texture map_utils map parse_map parsing))
PARSING_OBJS_BONUS = $(PARSING_SRC_BONUS:.c=.o)

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
	@printf "\033[1;32m|\033[32m                                                                              \033[m\r"
	@printf "\033[1;35m|\033[0;32m Compiling $@... \033[m\r"
	@cc -Wall -Wextra -Ofast -g3 -I $(INCLUDE) -I/usr/include -Imlx_linux -c $< -o ${<:.c=.o}
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

$(NAME_BONUS) : $(HEADERS_BONUS) $(OBJS_BONUS) $(SHAPE_OBJS_BONUS)\
	$(MAP_OBJS_BONUS) $(VECTOR_OBJS_BONUS) $(SOUND_OBJS_BONUS)\
	$(RENDER_OBJS_BONUS) $(INVENTORY_OBJS_BONUS) $(GAME_OBJS_BONUS)\
	$(SINGLETONS_OBJS_BONUS) $(SPRITES_OBJS_BONUS) $(INIT_OBJS_BONUS)\
	$(GARBAGE_OBJS_BONUS) $(WAVE_OBJS_BONUS)  $(EVENTS_OBJS_BONUS) $(PARSING_OBJS_BONUS)
	@printf "\033[K\033[1;32m| Cub3d bonus: compiled                |\n\033[m"
	@make --no-print-directory -C libft/
	@make --no-print-directory -C cjson/ > /dev/null
	@rm -f cjson/*.so
	@cc $(OBJS_BONUS) -O3 $(SHAPE_OBJS_BONUS) $(MAP_OBJS_BONUS)\
		$(VECTOR_OBJS_BONUS) $(SOUND_OBJS_BONUS) $(RENDER_OBJS_BONUS)\
		$(INVENTORY_OBJS_BONUS) $(GAME_OBJS_BONUS) $(SINGLETONS_OBJS_BONUS)\
		$(SPRITES_OBJS_BONUS) $(INIT_OBJS_BONUS) $(GARBAGE_OBJS_BONUS) $(WAVE_OBJS_BONUS) $(EVENTS_OBJS_BONUS) $(PARSING_OBJS_BONUS) $(MINIAUDIO) $(MLXFLAGS)\
		-lpthread -ldl -Lcjson/ -lcjson $(LIBFT) -o $(NAME_BONUS)
	@printf "\033[1;32m========================================\n"
	@printf "|            BONUS FINISHED !          |\n"
	@printf "========================================\n\033[m"
	@setterm -cursor on

clean:
	@printf "\033[1;31m========================================\n"
	@printf "|            CUB3D CLEANING            |\n"
	@printf "========================================\n\033[m"
	@printf "\033[K\033[1;31m|\033[1;33m Destroying objects                   \033[1;31m|\n\033[m"
	@make --no-print-directory clean -C libft/
	@make --no-print-directory clean -C cjson/
	@rm -f $(OBJS) $(SHAPE_OBJS) $(MAP_OBJS) $(VECTOR_OBJS)
	@rm -f $(OBJS_BONUS) $(SHAPE_OBJS_BONUS) $(MAP_OBJS_BONUS)\
		$(VECTOR_OBJS_BONUS) $(SOUND_OBJS_BONUS) $(RENDER_OBJS_BONUS)\
		$(INVENTORY_OBJS_BONUS) $(GAME_OBJS_BONUS) $(SINGLETONS_OBJS_BONUS)\
		$(SPRITES_OBJS_BONUS) $(INIT_OBJS_BONUS) $(GARBAGE_OBJS_BONUS) $(WAVE_OBJS_BONUS) $(EVENTS_OBJS_BONUS) $(PARSING_OBJS_BONUS)
	@printf "\033[1;31m========================================\n\033[m"

fclean: clean
	@printf "\033[K\033[1;31m|\033[1;31m Destroying all                       \033[1;31m|\n\033[m"
	@make --no-print-directory fclean -C libft/
	@rm -f $(NAME) $(NAME_BONUS)
	@printf "\033[1;31m========================================\n\033[m"

re: fclean all

.PHONY: all clean fclean re
