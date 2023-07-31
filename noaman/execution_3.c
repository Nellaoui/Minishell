/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:39:46 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/31 10:42:41 by aziyani          ###   ########.fr       */
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
	int		pfds[2]; // this is the variable which we pipe it inchalah pfds[0] = input of the pipe pfds[1] = output of the pipe
	t_node	*node;

	pipe(pfds);
	pid = fork(); // here we use this fork() to make a child proccess, cuz 
	if (pid == 0)
	{
		dup2(prev_in, STDIN_FILENO); // in the first time prev_in were be 0 so maghayw93 walo wlkn lmra tanya rankono 3mrnah ltaht
		if (cmd->next)
			dup2(pfds[1], STDOUT_FILENO);
		close(pfds[0]);
		setup_redirects(cmd, envi); // kador 3la tal pipe red ekatsetapihom
		exec_cmd(cmd->args, env);
	}
	else
	{
		close(pfds[1]); // remove leaks of file descriptor
		prev_in = dup(pfds[0]); // pfds[0] hwa lifih linput katreturnih fdak lvariable
		waitpid(pid, NULL, 0); // waitina hna bach maytkhrb9onach lproccess hit kaykhdmo fd9a
	}
	if (cmd->next)
		exec_compound_cmd(cmd->next, prev_in, env, envi);
}

// =========================================================================

void	exec_signal(t_cmd *cmd, char **env, t_env *envi, pid_t	pid)
{
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		setup_redirects(cmd, envi);
		if (check_builtin(cmd->args))
			exit(ft_built_in(cmd, envi));
		else
			exec_cmd(cmd->args, env);
	}
	else
	{
		wait(NULL);
		signal(SIGINT, ft_signal);
	}
}

// =========================================================================
// this is the finc() that execute the simple command

void	exec_simple_cmd(t_cmd *cmd, char **env, t_env *envi)
{
	pid_t	pid;
	int		in;
	int		out;

	if (check_builtin(cmd->args))
	{
		in = dup(0);
		out = dup(1);
		setup_redirects(cmd, envi);
		if (check_builtin(cmd->args))
		{
			ft_built_in(cmd, envi);
		}
		else
		{
			exec_cmd(cmd->args, env);
		}
		dup2(0, in);
		dup2(1, out);
		return ;
	}
	pid = fork();
	signal(SIGINT, SIG_IGN);
	exec_signal(cmd, env, envi, pid);
}

// =========================================================================
// this is the func() that execute all of execution part.

void	ft_execute(t_cmd *cmd, char **env, t_env *envi)
{
	t_cmd	*curr;
	int		size;

	size = 0;
	curr = cmd;
	while (curr) // in this loop we count the size of the linked list
	{
		++size;
		curr = curr->next;
	}
	if (size == 1) // so if the linked list size equal 1, so that we have only one argument like [ls], and this named a simple command.
	{
		exec_simple_cmd(cmd, env, envi); // simple_cmd = ls or ls -la
	}
	else // else, that mean the linked list size equal more than 1, so that we have more than one argument like [ls | cat -e], and thsi named a compound command.
		exec_compound_cmd(cmd, 0, env, envi); // compound_cmd = ls -la | echo ziyani | cat -e
}

// =========================================================================