/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:39:31 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/30 13:28:46 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

int	ft_count_link(t_node *node)
{
	t_node	*tmp;
	int		i;

	tmp = node;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

// =========================================================================

int	ft_built_in_2(t_cmd *cmd, t_env *env)
{
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
		else
			cmd->args->data = NULL;
		return (ft_exit(cmd->args, cmd->args->data));
	}
	return (0);
}

// =========================================================================

int	ft_built_in(t_cmd *cmd, t_env *env)
{
	int	ac;

	if (ft_strncmp("echo", cmd->args->data, 5) == 0)
		return (ft_echo(cmd->args, ft_count_link(cmd->args)));
	if (ft_strncmp("cd", cmd->args->data, 3) == 0)
	{
		ac = ft_count_link(cmd->args);
		if (ac > 1)
		{
			cmd->args = cmd->args->next;
			return (ft_cd(cmd->args->data, env));
		}
		else
			return (ft_cd(NULL, env));
	}
	if (ft_strncmp("pwd", cmd->args->data, 4) == 0)
		return (ft_pwd());
	if (ft_strncmp("export", cmd->args->data, 7) == 0)
	{
		if (cmd->args->next)
			cmd->args = cmd->args->next;
		return (ft_export(&g_global.env, cmd->args->data));
	}
	ft_built_in_2(cmd, env);
	return (0);
}

// =========================================================================