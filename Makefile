# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/07/27 22:59:52 by nelallao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
# FFLAGS = -fsanitize=address -g
# SRC = noaman/minishell.c ./includes/libft_func.c ./ayoub/execution.c
SRC= minishell.c execution.c libft_func.c libft_func_2.c libft_func_3.c libft_func_4.c check.c expend.c expend_2.c inserting.c outils.c token.c outils_2.c get_next_line.c get_next_line_utils.c builtin.c
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix obj/, $(OBJ))
OBJ_DIR=obj/

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) -lreadline $(LFLAGS) $(FFLAGS) -L /Users/nelallao/.brew/opt/readline/lib/  $(OBJ)  -o $(NAME)

obj/%.o: noaman/%.c
	$(CC) -c $< -o $@ -I /Users/nelallao/.brew/opt/readline/include/

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
