/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:43:16 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/29 14:15:56 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ===========================================================================

void	exec_cmd(t_node *cmd, char **env)
{
	char **paths = ft_split(get_value("PATH", g_global.env), ':');
	char **e_cmd = linked_list_to_array(cmd);
	e_cmd[0] = get_cmd(paths, e_cmd[0]);
	if (e_cmd[0] == NULL)
	{
		dprintf(2, "minishell: command not found\n");
		exit (127);
	}
	execve(e_cmd[0], e_cmd, env);
	printf("somthing went wrong\n");
	exit (1);
}

// ===========================================================================

char **linked_list_to_array(t_node *head)
{
	int		len;
	t_node	*current;
	char	**doubleArray;
	int		i;

	i = 0;
	current	= head;
	len = 0;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	doubleArray = (char **)malloc((len + 1) * sizeof(char *));
	current = head;
	while (i < len)
	{
		doubleArray[i] = current->data;
		current = current->next;
		i++;
	}
	doubleArray[len] = 0;
	return (doubleArray);
}

// ===========================================================================

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd[0] == '.')
		if (check_cmd(cmd) == 1)
			return (cmd);
	if (cmd[0] == '/')
	{
		cmd = ft_strchr(cmd, '/');
		if (strrchr(cmd, '/') == NULL)
			return (0);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

// ===========================================================================

int	check_cmd(char *cmd)
{
	if (access(cmd, F_OK) < 0)
	{
		dprintf(2, "No such file or directory: %s\n", cmd);
		exit(126);
	}
	if (access(cmd, X_OK) < 0)
	{
		dprintf(2, "Permission denied: %s\n", cmd);
		exit(126);
	}
	return (1);
}

// ===========================================================================

void	setup_heredoc(char *del, int expand, t_env *envi)
{
	char *line;
	int	pfds[2];

	pipe(pfds);
	while (1)
	{
		line = get_next_line(0);
		if (strnstr(line, del, strlen(del))) // need ft_
			break ;
		if (expand)
			dprintf(pfds[1], "%s", get_expanded(line, envi)); // printf()
		else
			dprintf(pfds[1], "%s", line);
		free(line);
	}
	free(line);
	dup2(pfds[0], STDIN_FILENO);
}

// ===========================================================================

void	handle_heredoc(t_node *curr, t_env *envi)
{
	while (curr)
	{
		setup_heredoc(curr->data, curr->quote, envi);
		curr = curr->next;
	}
}

// ===========================================================================

void	setup_redirects(t_cmd *cmd, t_env *envi)
{
	int fd;
	if (cmd->in_reds)
	{
		while (cmd->in_reds)
		{
			if (cmd->in_reds->data)
			{
				fd = open(cmd->in_reds->data, O_RDONLY);
				dup2(fd, STDIN_FILENO);
			}
			else
				dprintf(2, "minishell: %s: No such file or directory\n", cmd->in_reds->data);
			cmd->in_reds = cmd->in_reds->next;
		}
	}
	if (cmd->out_reds)
	{
		while (cmd->out_reds)
		{
			if (cmd->out_reds->type == OUT)
			{
				fd = open(cmd->out_reds->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
				dup2(fd, STDOUT_FILENO);
			}
			else if (cmd->out_reds->type == APPEND)
			{
				fd = open(cmd->out_reds->data, O_RDWR | O_CREAT | O_APPEND, 0644);
				dup2(fd, STDOUT_FILENO);
			}
			cmd->out_reds = cmd->out_reds->next;
		}
	}
	if (cmd->her_reds)
	{
		handle_heredoc(cmd->her_reds, envi);
	}
}

// ===========================================================================

int	check_builtin(t_node *head)
{
	if (ft_strncmp(head->data, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(head->data, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(head->data, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(head->data, "export", 7) == 0)
		return (1);
	if (ft_strncmp(head->data, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(head->data, "env", 4) == 0)
		return (1);
	if (ft_strncmp(head->data, "exit", 5) == 0)
		return (1);
	return (0);
}

// ===========================================================================

void	exec_compound_cmd(t_cmd *cmd, int prev_in, char **env, t_env *envi)
{
	pid_t	pid;
	int		pfds[2];
	t_node	*node;

	pipe(pfds);
	pid = fork();
	if (pid == 0)
	{
		dup2(prev_in, STDIN_FILENO);
		if (cmd->next)
			dup2(pfds[1], STDOUT_FILENO);
		close(pfds[0]);
		setup_redirects(cmd, envi);
		// if (check_builtin(cmd->args))
		// 	ft_built_in(cmd);
		// else
			exec_cmd(cmd->args, env);
	}
	else
	{
		close(pfds[1]);
		prev_in = dup(pfds[0]);
		waitpid(pid, NULL, 0);
	}
	if (cmd->next)
		exec_compound_cmd(cmd->next, prev_in, env, envi);
}

// ===========================================================================

void	exec_simple_cmd(t_cmd *cmd, char **env, t_env *envi)
{
	pid_t	pid;

	if (check_builtin(cmd->args))
	{
		int __in = dup(0);
		int __out = dup(1);
		setup_redirects(cmd, envi);
		ft_built_in(cmd);
		dup2(0, __in);
		dup2(1, __out);
		return ;
	}
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		setup_redirects(cmd, envi);
		if (check_builtin(cmd->args))
			exit(ft_built_in(cmd));
			
		
		else
			exec_cmd(cmd->args, env);
	}
	else
	{
		wait(NULL);
		signal(SIGINT, ft_signal);
	}
}

// ===========================================================================

void	ft_execute(t_cmd *cmd, char **env, t_env *envi)
{
	t_cmd	*curr;
	int		size = 0;

	curr = cmd;
	while (curr)
	{
		++size;
		curr = curr->next;
	}
	if (size == 1)
		exec_simple_cmd(cmd, env, envi);
	else
		exec_compound_cmd(cmd, 0, env, envi);
}

// ===========================================================================

t_env	*ft_setup_env(char **env_main)
{
	t_env	*list;

	char	**key_value;
	int		j;

	list = NULL;
	j = -1;
	while (env_main[++j])
	{
		key_value = ft_split(env_main[j], '='); 
		add_node(&list, create_node(key_value[0], key_value[1]));
		free_arr(key_value);
	}
	return (list);
}

// ===========================================================================

void	add_node(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	tmp = *list;
	if (*list == NULL)
		*list = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

// ===========================================================================

t_env   *create_node(char *key, char *value)
{
	t_env   *node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

// ===========================================================================

void	ft_command(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (tmp)
	{
		tmp = tmp->next;
	}
}

// ===========================================================================

int	ft_count_link(t_node *node)
{
	t_node *tmp;

	tmp = node;
	int	i;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

// ===========================================================================

int	ft_built_in(t_cmd *cmd)
{
	int ac;

	if (ft_strncmp("echo", cmd->args->data, 5) == 0)
		return (ft_echo(cmd->args, ft_count_link(cmd->args)));
	if (ft_strncmp("cd", cmd->args->data, 3) == 0)
	{
		ac = ft_count_link(cmd->args);
		if (ac > 1)
		{
			cmd->args = cmd->args->next;
			return (ft_cd(cmd->args->data));
		}
		else
			return (ft_cd(NULL));
	}
	if (ft_strncmp("pwd", cmd->args->data, 4) == 0)
		return (ft_pwd());
	if (ft_strncmp("export", cmd->args->data, 7) == 0)
	{
		if (cmd->args->next)
			cmd->args = cmd->args->next;
		return (ft_export(&g_global.env, cmd->args->data));
	}
	if (ft_strncmp("unset", cmd->args->data, 6) == 0)
	{
		if (cmd->args->next)
			cmd->args = cmd->args->next;
		return (ft_unset(cmd->args->data));
	}
	if (ft_strncmp("env", cmd->args->data, 4) == 0)
		return (ft_env());
	if (ft_strncmp("exit", cmd->args->data, 5) == 0)
	{
		if (cmd->args->next)
			cmd->args = cmd->args->next;
		if (cmd->args->next)
			return (ft_exit("ziyani"));
		return (ft_exit(cmd->args->data));
	}
	return (0);
}

// ===========================================================================