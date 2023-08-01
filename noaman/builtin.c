/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:48:52 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/01 17:49:05 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

int	ft_echo(t_node *args, int number_of_arg)
{
	int	i;
	int	n_line;

	i = 0;
	n_line = 1;
	args = args->next;
	while (args && args->data && number_of_arg > 1
		&& ft_strncmp(args->data, "-n", 3) == 0)
	{
		n_line = 0;
		args = args->next;
	}
	while (args && args->data && i <= number_of_arg)
	{
		printf("%s ", args->data);
		i++;
		args = args->next;
	}
	if (n_line)
		printf("\n");
	return (0);
}

// ==========================================================================

int	ft_env(void)
{
	t_env	*tmp;

	tmp = g_global.env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

// =========================================================================

int	ft_modify_node(char	*export, char	*key)
{
	if (ft_strncmp(export, key, ft_strlen(key + 1)) == 0)
		return (1);
	return (0);
}

int	ft_pwd(void)
{
	t_env	*tmp;

	tmp = g_global.env;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->key, 4) == 0)
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
