/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:58 by nelallao          #+#    #+#             */
/*   Updated: 2023/06/22 13:01:55 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_env  // we use this struct to store env as linkedlist
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct s_global // we use this struct to creat a global varibal that contain env so we can use it anywhere
{
	t_env	*g_env;
	int		exit_status;
}	t_global;

t_global	global;

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
// int		ft_strcmp(char *s1, char *s2);
// int		ft_strlen(const char *str);
// char	*ft_strchr(const char *scanned, int searched);
// char	*ft_strdup(const char *s1);
// char	*ft_substr(char const *s, unsigned int start, int len);
// void	ft_putstr_fd(char *s, int fd);
// char	**ft_split(char const *s, char c);
/*-------------------------------*/


/********** UTILS  *******************/
t_env   *create_node(char *key, char *value);
void	add_node(t_env **list, t_env *new_node);
char	*get_key_env(char *env, int *i);
char	*get_value_env(char *env, int *i);
int		ft_env();
int	ft_export(t_env **export, char *str);

#endif
