# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/07/19 21:54:25 by nelallao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror  # -fsanitize=address -g
LFLAGS = -lreadline
# FFLAGS = -fsanitize=address -g
SRC = noaman/minishell.c ./includes/libft_func.c ./ayoub/execution.c
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix obj/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(LFLAGS) $(FFLAGS) $(OBJ) -o $(NAME)

obj/%.o: %.c minishell.h
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
