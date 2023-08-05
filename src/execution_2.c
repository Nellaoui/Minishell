/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:39:31 by aziyani           #+#    #+#             */
/*   Updated: 2023/08/03 16:38:13 by aziyani          ###   ########.fr       */
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

int	ft_built_in_2(t_node *args)
{
	if (ft_strncmp("unset", args->data, 6) == 0)
	{
		if (args->next)
			args = args->next;
		return (ft_unset(args->data));
	}
	if (ft_strncmp("env", args->data, 4) == 0)
		return (ft_env());
	if (ft_strncmp("exit", args->data, 5) == 0)
	{
		if (args->next)
			args = args->next;
		else
			args->data = NULL;
		return (ft_exit(args, args->data));
	}
	return (0);
}

// =========================================================================

int	ft_built_in(t_node *args, t_env *env)
{
	int	ac;

	if (ft_strncmp("echo", args->data, 5) == 0)
		return (ft_echo(args, ft_count_link(args)));
	if (ft_strncmp("cd", args->data, 3) == 0)
	{
		ac = ft_count_link(args);
		if (ac > 1)
		{
			args = args->next;
			return (ft_cd(args->data, env));
		}
		else
			return (ft_cd(NULL, env));
	}
	if (ft_strncmp("pwd", args->data, 4) == 0)
		return (ft_pwd());
	if (ft_strncmp("export", args->data, 7) == 0)
		return (ft_export(&g_global.env, args));
	ft_built_in_2(args);
	return (0);
}

// =========================================================================
