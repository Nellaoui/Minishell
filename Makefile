# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/07/23 19:05:38 by nelallao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
# FFLAGS = -fsanitize=address -g
# SRC = noaman/minishell.c ./includes/libft_func.c ./ayoub/execution.c
SRC= minishell.c execution.c libft_func.c
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix obj/, $(OBJ))
OBJ_DIR=obj/

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) -fsanitize=address -g $(LFLAGS) $(FFLAGS) $(OBJ) -o $(NAME)

obj/%.o: noaman/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: ayoub/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: includes/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
