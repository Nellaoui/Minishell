# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/06/22 13:01:24 by aziyani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
# FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
SRC = ./source/main/minishell.c ./includes/libft_func.c \
		./source/main/lst_utiles.c ./source/builtins/env.c \
		./source/builtins/export.c

all : $(NAME)

$(NAME) :$(SRC)
	@make -C includes/libft
	@$(CC) $(FLAGS) $(LFLAGS) $(SRC) includes/libft/libft.a -o $(NAME)

clean :
	@$(RM)
	@make clean -C includes/libft

fclean : clean
	@$(RM) $(NAME)
	@make fclean -C includes/libft

re : fclean all
