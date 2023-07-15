/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:58 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/15 12:56:19 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_type
{
	PIPE = 1,
	IN, // <
	OUT, // >
	APPEND, // >>
	HERDOC, // <<
	ARRGUMENT
}	t_type;

typedef struct s_node t_node;

// typedef struct s_cmd
// {
// 	char			*word;
// 	t_type			type;
// 	struct s_cmd	*next;
// }	t_cmd;


// typedef struct s_cmd
// {
// 	t_node			*arguments;
// 	// t_node			*in_files;
// 	struct s_cmd	*next;
// }	t_cmd;

typedef struct s_node
{
	char			*data;
	int				type;
	struct s_node	*next;
	struct s_node	*previous;
} t_node;

typedef struct s_cmd
{
	t_node			*args;
	t_node			*out_reds;
	t_node			*in_reds;
	t_node			*her_reds;
	int				type_in;
	struct s_cmd	*next;
}	t_cmd;

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
char	*ft_strjoin(char const *s1, char const *s2);
/*-------------------------------*/
#endif
