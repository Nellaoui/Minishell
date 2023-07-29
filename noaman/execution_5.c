/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:40:12 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/29 20:30:20 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

void	setup_heredoc(char *del, int expand, t_env *envi)
{
	char	*line;
	int		pfds[2];

	pipe(pfds);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strnstr(line, del, ft_strlen(del)))
			break ;
		if (expand)
			dprintf(pfds[1], "%s", get_expanded(line, envi));
		else
			dprintf(pfds[1], "%s", line);
		free(line);
	}
	free(line);
	dup2(pfds[0], STDIN_FILENO);
}

// =========================================================================

void	handle_heredoc(t_node *curr, t_env *envi)
{
	while (curr)
	{
		setup_heredoc(curr->data, curr->quote, envi);
		curr = curr->next;
	}
}

// =========================================================================

void	ft_help_in_red(t_cmd *cmd, int fd)
{
	while (cmd->in_reds)
	{
		if (cmd->in_reds->data)
		{
			if (access(cmd->in_reds->data, F_OK) == 0)
			{
				fd = open(cmd->in_reds->data, O_RDONLY);
				dup2(fd, STDIN_FILENO);
			}
			else
				dprintf(2, "minishell: %s: No such file or directory\n",
					cmd->in_reds->data);
		}
		else
			dprintf(2, "minishell: %s: No such file or directory\n",
				cmd->in_reds->data);
		cmd->in_reds = cmd->in_reds->next;
	}
}

// =========================================================================

void	ft_help_out_red(t_cmd *cmd, int fd)
{
	while (cmd->out_reds)
	{
		if (cmd->out_reds->type == OUT)
		{
			fd = open(cmd->out_reds->data, O_RDWR
					| O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (cmd->out_reds->type == APPEND)
		{
			fd = open(cmd->out_reds->data, O_RDWR
					| O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		cmd->out_reds = cmd->out_reds->next;
	}
}

// =========================================================================

void	setup_redirects(t_cmd *cmd, t_env *envi)
{
	int	fd;

	if (cmd->in_reds)
		ft_help_in_red(cmd, fd);
	if (cmd->out_reds)
		ft_help_out_red(cmd, fd);
	if (cmd->her_reds)
		handle_heredoc(cmd->her_reds, envi);
}

// =========================================================================