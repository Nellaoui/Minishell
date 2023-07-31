/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:43:16 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/30 13:30:47 by aziyani          ###   ########.fr       */
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
		dprintf(2, "minishell: command not found\n");
		exit (127);
	}
	execve(e_cmd[0], e_cmd, env);
	printf("somthing went wrong\n");
	exit (1);
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

// =========================================================================
