# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:31:19 by nelallao          #+#    #+#              #
#    Updated: 2023/06/12 12:13:27 by nelallao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
# FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
SRC = minishell.c libft_func.c

all : $(NAME)

$(NAME) :$(SRC)
	@$(CC) $(FLAGS) $(LFLAGS) $(SRC) -o $(NAME)

clean :
	@$(RM)
fclean : clean
	@$(RM) $(NAME)
re : fclean all
