# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/06/22 10:24:46 by nelallao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
# FFLAGS = fsanitize=address -g
SRC = minishell.c libft_func.c
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix obj/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(LFLAGS) $(FFLAGS) $(OBJ) -o $(NAME)

obj/%.o: %.c minishell.h
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
