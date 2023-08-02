# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/07/31 21:26:10 by aziyani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
LIBFT = includes/libft/libft.a
# FFLAGS = -fsanitize=address -g
# SRC = noaman/minishell.c ./includes/libft_func.c ./ayoub/execution.c
SRC= minishell.c check.c expend.c expend_2.c inserting.c outils.c token.c outils_2.c \
	execution.c get_next_line.c get_next_line_utils.c builtin.c builtin_2.c builtin_3.c \
	execution_2.c execution_3.c execution_4.c execution_5.c help_minishell.c
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix obj/, $(OBJ))
OBJ_DIR=obj/

all: $(OBJ_DIR) $(NAME) $(LIBFT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -lreadline $(LFLAGS) $(FFLAGS) $(FLAGS) -L /Users/nelallao/.brew/opt/readline/lib/  $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@make -C includes/libft

obj/%.o: noaman/%.c
	$(CC) -c $< -o $@ -I /Users/nelallao/.brew/opt/readline/include/

clean:
	@make clean -C includes/libft
	@$(RM) $(OBJ)

fclean: clean
	@make fclean -C includes/libft
	@$(RM) $(NAME)

re: fclean all
	@make re -C includes/libft
