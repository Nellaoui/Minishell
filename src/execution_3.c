/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:39:46 by aziyani           #+#    #+#             */
/*   Updated: 2023/08/02 23:54:23 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

int	check_builtin(t_node *head)
{
	if (head)
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
	}
	return (0);
}

// =========================================================================

void	exec_compound_cmd(t_cmd *cmd, int prev_in, char **env, t_env *envi)
{
	pid_t	pid;
	int		pfds[2];
	int		status;

	status = 0;
	pipe(pfds);
	pid = fork();
	if (pid == 0)
	{
		dup2(prev_in, STDIN_FILENO);
		if (cmd->next)
			dup2(pfds[1], STDOUT_FILENO);
		close(pfds[0]);
		setup_redirects(cmd, envi);
		exec_cmd(cmd->args, env);
	}
	else
	{
		close(pfds[1]);
		prev_in = dup(pfds[0]);
		waitpid(pid, &status, 0);
	}
	g_global.exit_status = status >> 8;
	if (cmd->next)
		exec_compound_cmd(cmd->next, prev_in, env, envi);
}

// =========================================================================

void	exec_signal(t_cmd *cmd, char **env, t_env *envi, pid_t	pid)
{
	int	status;

	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		setup_redirects(cmd, envi);
		if (check_builtin(cmd->args))
			exit(ft_built_in(cmd->args, envi));
		else
			exec_cmd(cmd->args, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_global.exit_status = status >> 8;
		signal(SIGINT, ft_signal);
	}
}

// =========================================================================

void	exec_simple_cmd(t_cmd *cmd, char **env, t_env *envi)
{
	pid_t	pid;
	int		__in;
	int		__out;

	if (check_builtin(cmd->args))
	{
		__in = dup(0);
		__out = dup(1);
		setup_redirects(cmd, envi);
		ft_built_in(cmd->args, envi);
		dup2(0, __in);
		dup2(1, __out);
		return ;
	}
	pid = fork();
	signal(SIGINT, SIG_IGN);
	exec_signal(cmd, env, envi, pid);
}

// =========================================================================

void	ft_execute(t_cmd *cmd, char **env, t_env *envi)
{
	t_cmd	*curr;
	int		size;

	size = 0;
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

// =========================================================================
