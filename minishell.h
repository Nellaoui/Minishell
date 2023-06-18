/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:58 by nelallao          #+#    #+#             */
/*   Updated: 2023/06/17 19:29:35 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum type
{
	PIPE = 1,
	IN,
	OUT,
	APPEND,
	HERDOC,
	ARRGUMENT,
}	e_type;

typedef struct s_node
{
	char			*data;
	int				type;
	struct s_node	*next;
	struct s_node	*previous;
	int				index;
} t_node;

typedef struct s_token
{
	int		i;
	int		double_quote;
	int		single_quote;
	int		start;
	char	*res;
} t_token;
/*---------libft-----------------*/
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *str);
char	*ft_strchr(const char *scanned, int searched);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, int len);
void	ft_putstr_fd(char *s, int fd);
/*-------------------------------*/
#endif
