/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:46:34 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/29 19:36:56 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

int	ft_check_key(char	**key_value)
{
	int	i;

	if (key_value[0][0] != '_' && !ft_isalpha(key_value[0][0]))
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	i = 1;
	while (key_value[0][i])
	{
		if (!(ft_isalnum(key_value[0][i])))
		{
			if (key_value[0][i] != '_')
			{
				ft_putstr_fd("not a valid identifier\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	add_env_variable(t_env **export, char **key_value)
{
	int		i;
	int		added;
	t_env	*tmp;

	tmp = *export;
	i = 0;
	added = 0;
	while (tmp)
	{
		if (!ft_strncmp(key_value[0], tmp->key, ft_strlen(tmp->key) + 1))
		{
			tmp->value = ft_strdup(key_value[1]);
			added = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!added)
		add_node(export, create_node(key_value[0], key_value[1]));
}

int	ft_export(t_env **export, char *str)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	**key_value;
	int		i;

	tmp = *export;
	key_value = ft_split(str, '=');
	if (!key_value[1])
	{
		tmp2 = g_global.env;
		while (tmp2)
		{
			printf("declare -x %s=\"%s\"\n", tmp2->key, tmp2->value);
			tmp2 = tmp2->next;
		}
		return (1);
	}
	if (!ft_check_key(key_value))
		add_env_variable(export, key_value);
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
			write (2, "exit: asf: numeric argument required\n", 37);
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
	if (i > 2)
		exit(write(2, "exit: too many arguments\n", 21) != 0);
	else
	{
		is_alpha(data);
		exit_number = ft_atoi(data);
		exit (exit_number);
	}
	return (0);
}

// =========================================================================