# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 17:19:09 by rukkyaa           #+#    #+#              #
#    Updated: 2023/01/19 00:15:48 by rukkyaa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c 

BONUS_OBJS = $(BONUS_SRC:.c=.o)

# CHECKING FUNCTION
CHECKING = $(addprefix ft_, $(addsuffix .c, \
	isalpha isdigit isalnum isascii isprint))
CHECKING_OBJS = $(CHECKING:%.c=.build/%.o)

# STRING FUNCTIONS
STRING = $(addprefix ft_, $(addsuffix .c, \
			strlen toupper tolower strchr strrchr strncmp strdup strnstr \
			strjoin strmapi strtrim substr split striteri strlcat strlcpy))
STRING_OBJS = $(STRING:%.c=.build/%.o)

# CONVERTION FUNCTION
CONVERTION = $(addprefix ft_, $(addsuffix .c, \
			itoa atoi))
CONVERTION_OBJS = $(CONVERTION:%.c=.build/%.o)

# MEMORY FUNCTION
MEMORY = $(addprefix ft_, $(addsuffix .c, \
			memset bzero memcpy memchr memcmp calloc memmove))
MEMORY_OBJS = $(MEMORY:%.c=.build/%.o)

# PRINT FUNCTION
PRINT = $(addprefix ft_, $(addsuffix .c, \
			putnbr_fd putchar_fd putstr_fd putendl_fd))
PRINT_OBJS = $(PRINT:%.c=.build/%.o)

# UTILS
AR = ar -rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
HEADERS = -I includes/

.build/%.o : %.c
		@setterm -cursor off
		@mkdir -p .build
		@printf "\033[1;32m|\033[32m                                      \033[m\r"
		@printf "\033[1;35m|\033[0;32m Compiling $@... \033[m\r"
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

$(NAME): \
	$(STRING_OBJS) $(MEMORY_OBJS) $(CONVERTION_OBJS) \
	$(PRINT_OBJS) $(CHECKING_OBJS)
	@$(AR) $(NAME) $(STRING_OBJS) $(MEMORY_OBJS) $(CONVERTION_OBJS) \
	$(PRINT_OBJS) $(CHECKING_OBJS)
	@printf "\033[K\033[1;32m| Libft        : compiled              |\n\033[m"
	@setterm -cursor on

bonus: $(OBJS) $(BONUS_OBJS)
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	
clean:
	@$(RM) .build $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
