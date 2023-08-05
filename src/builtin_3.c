/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:46:34 by aziyani           #+#    #+#             */
/*   Updated: 2023/08/05 23:33:09 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

int	ft_check_key(char	*key_value)
{
	int	i;

	if (key_value[0] != '_' && !ft_isalpha(key_value[0]))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(key_value, 2);
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	i = 1;
	while (key_value[i])
	{
		if (!(ft_isalnum(key_value[i])) && key_value[i] != '_')
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(key_value, 2);
			ft_putstr_fd("not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_env_variable(t_env **export, char *key, char *value, int is_qual)
{
	int		added;
	t_env	*tmp;

	tmp = *export;
	added = 0;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(tmp->key) + 1))
		{
			if (is_qual == 0)
			{
				added = 1;
				break ;
			}
			free(tmp->value);
			tmp->value = ft_strdup(value);
			tmp->is_equal = is_qual;
			added = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!added)
		add_node(export, create_node(key, value, is_qual));
}

int	ft_export(t_env **export, t_node *arg)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	**e_cmd;

	tmp = *export;
	e_cmd = linked_list_to_array(arg);
	if (ft_count_link(arg) == 1)
	{
		tmp2 = g_global.env;
		while (tmp2)
		{
			printf("declare -x %s=\"%s\"\n", tmp2->key, tmp2->value);
			tmp2 = tmp2->next;
		}
		return (1);
	}
	check_and_set_vr(export, e_cmd);
	free(e_cmd);
	return (0);
}

// =========================================================================

void	is_alpha(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!(string[i] >= '0' && string[i] <= '9'))
		{
			write (2, "minishell: exit: asf: numeric argument required\n", 37);
			exit (255);
		}
		i++;
	}
}

int	ft_exit(t_node *status, char *data)
{
	int		exit_number;
	int		i;
	t_node	*x;

	i = 0;
	x = status;
	if (data == NULL)
		exit (0);
	while (x)
	{
		i++;
		x = x->next;
	}
	if (i >= 2)
		write(2, "minishell: exit: too many arguments\n", 25);
	else
	{
		is_alpha(data);
		exit_number = ft_atoi(data);
		g_global.exit_status = exit_number;
		exit (exit_number);
	}
	return (0);
}

// =========================================================================
