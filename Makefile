# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/07/24 18:55:29 by aziyani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
# FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
# FFLAGS = -fsanitize=address -g
# SRC = noaman/minishell.c ./includes/libft_func.c ./ayoub/execution.c
SRC= minishell.c execution.c libft_func.c get_next_line.c get_next_line_utils.c
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix obj/, $(OBJ))
OBJ_DIR=obj/

all : $(NAME)

$(NAME) :$(SRC)
	@make -C includes/libft
	@$(CC) $(FLAGS) $(LFLAGS) $(SRC) includes/libft/libft.a -o $(NAME)

clean :
	@$(RM)
	@make clean -C includes/libft
$(NAME): $(OBJ)
	$(CC) $(LFLAGS) $(FFLAGS) $(OBJ) -o $(NAME)

fclean : clean
	@$(RM) $(NAME)
	@make fclean -C includes/libft

re : fclean all
