# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/06/22 11:14:00 by aziyani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
# FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
SRC = ./source/main/minishell.c ./includes/libft_func.c \
		./source/main/lst_utiles.c ./source/builtins/env.c

all : $(NAME)

$(NAME) :$(SRC)
	@$(CC) $(FLAGS) $(LFLAGS) $(SRC) -o $(NAME)

clean :
	@$(RM)
fclean : clean
	@$(RM) $(NAME)
re : fclean all
