/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:58 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/06 01:32:01 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "get_next_line.h"
# include "libft/libft.h"

typedef enum e_type
{
	PIPE = 1,
	IN,
	OUT,
	APPEND,
	HERDOC,
	ARRGUMENT
}	t_type;

typedef struct s_node	t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_equal;
	struct s_env	*next;
}	t_env;

typedef struct s_global
{
	t_env	*env;
	int		exit_status;
	int		s_in;
	int		s_out;
}	t_global;

t_global				g_global;

typedef struct s_node
{
	char			*data;
	int				type;
	int				quote;
	struct s_node	*next;
	struct s_node	*previous;
}	t_node;
typedef struct s_cmd
{
	t_node			*args;
	t_node			*out_reds;
	t_node			*in_reds;
	t_node			*her_reds;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	int		i;
	int		double_quote;
	int		single_quote;
	int		start;
	char	*res;
	int		len;
	int		j;
	char	*string;
	char	*identifire;
	char	*id;
	char	*value;
	int		check;
	int		to_free;
}	t_token;

/*-----------------builtin--------------------------*/
int		ft_cd(char *path, t_env *env);
int		ft_echo(t_node *args, int number_of_arg);
int		ft_env(void);
int		ft_exit(t_node *status, char *data);
int		ft_modify_node(char	*export, char	*key);
int		ft_check_key(char	*key_value);
int		ft_export(t_env **export, t_node *arg);
int		ft_pwd(void);
int		ft_unset(char *str);
int		ft_built_in(t_node *args, t_env *env);
void	ft_command(t_node *node);
/*--------------------------------------------------*/
/*---------noaman-----------------*/

t_token	*ft_initialize(t_token *s);
void	ft_insert_token(t_node **head, char *data);
void	ft_insert_token_2(t_node **head, char *data, int type);
void	ft_display(t_node *head);
void	all_display(t_cmd	*cmd);
void	ft_splited(char *str, t_token *s, t_node **head);
void	ft_redrection(char *str, t_token *s, t_node **head);
void	ft_pipe(char *str, t_token *s, t_node **head);
t_node	*ft_token(char *str, t_node *head);
int		ft_check_quotes(char *str);
int		ft_syntax_error(t_node *head);
void	ft_type(t_node **head, t_token *s);
t_cmd	*ft_new_node(void);
t_cmd	*ft_insert_link(t_node *head);
char	*ft_subfree(char *str, int start, int len);
char	*get_index(char *string);
void	ft_inside_quote(t_token *s, char *str);
int		ft_is_valid(char c);
char	*get_value(char *id, t_env *envi);
int		get_str_len(char *data, t_env *envi);
char	*get_new_string(int str_len, char *data);
char	*get_expanded(char *data, t_env *envi);
void	ft_mini_expen(t_node *node, t_env *envi);
void	ft_expension(t_cmd *cmd, t_env *envi);
void	free_arr(char **s);
void	ft_rederct(char *str, t_token *s, t_node **head);
void	ft_quote(t_cmd *cmd);
void	ft_skip(t_token *s, char *data);
void	ft_frees_cmd(t_cmd *head);
char	*ft_if_remove(char *data, char *str);
void	ft_free_ls(t_node *head);
void	ft_help_get_len(t_token *s, char *data, t_env *envi);
void	ft_help_get_str(char *data, t_token *s);
char	*ft_readforfree(char *input);
void	ft_s_env(char **env);
char	*ft_free_new_str(t_token *s);
int		ft_empty(char *str);
int		ft_hundling(t_token *s, char *data, char *string);
int		ft_count_link(t_node *node);
/*-------------------------------*/
/*---------ayoub-----------------*/
void	exec_cmd(t_node *cmd, char **env);
void	setup_heredoc(char *del, int expand, t_env *envi);
void	handle_heredoc(t_node *curr, t_env *envi);
int		setup_redirects(t_cmd *cmd, t_env *envi);
void	exec_compound_cmd(t_cmd *cmd, int prev_in, char **env, t_env *envi);
void	exec_simple_cmd(t_cmd *cmd, char **env, t_env *envi);
void	ft_execute(t_cmd *cmd, char **env, t_env *envi);
t_env	*create_node(char *key, char *value, int is_qual);
void	add_node(t_env **list, t_env *new_node);
char	**linked_list_to_array(t_node *head);
char	*get_cmd(char **paths, char *cmd);
int		check_cmd(char *cmd);
void	exec_cmd(t_node *cmd, char **env);
int		ft_perror(char *s);
t_env	*ft_setup_env(char **env_main);
void	ft_signal(int sig);
void	ft_help_std_dup(char **env);
void	ft_help_std(void);
void	add_env_variable(t_env **export, char *key, char *value, int is_qual);
void	check_and_set_vr(t_env **export, char **e_cmd);

/*-------------------------------*/
#endif
