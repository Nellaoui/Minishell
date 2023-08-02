/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:43:16 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/03 00:04:23 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

void	exec_cmd(t_node *cmd, char **env)
{
	char	**paths;
	char	**e_cmd ;

	paths = ft_split(get_value("PATH", g_global.env), ':');
	e_cmd = linked_list_to_array(cmd);
	e_cmd[0] = get_cmd(paths, e_cmd[0]);
	if (e_cmd[0] == NULL)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		g_global.exit_status = 127;
		exit(127);
	}
	execve(e_cmd[0], e_cmd, env);
	ft_putstr_fd("minishell: command not found\n", 2);
	g_global.exit_status = 127;
	exit(g_global.exit_status);
}

// =========================================================================

char	**linked_list_to_array(t_node *head)
{
	int		len;
	t_node	*current;
	char	**array;
	int		i;

	i = 0;
	current = head;
	len = 0;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	array = (char **)malloc((len + 1) * sizeof(char *));
	current = head;
	while (i < len)
	{
		array[i] = current->data;
		current = current->next;
		i++;
	}
	array[len] = 0;
	return (array);
}

// =========================================================================

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
	while (paths && *paths)
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

// =========================================================================

int	check_cmd(char *cmd)
{
	char	*s;

	s = NULL;
	if (access(cmd, F_OK) < 0)
	{
		s = cmd;
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
		g_global.exit_status = 1;
		exit(g_global.exit_status);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd("Permission denied: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
		g_global.exit_status = 1;
		exit(g_global.exit_status);
	}
	return (1);
}

// =========================================================================

void	ft_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
	g_global.exit_status = 1;
	exit(g_global.exit_status);
}
