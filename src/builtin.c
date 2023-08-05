/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:48:52 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/04 20:13:28 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

typedef struct t_data
{
	int	n_line;
	int	index;
	int	break_me_please_dady;
}	t_data;

t_node	*ft_help_echo(t_node *args, t_data *data)
{
	args = args->next;
	data->break_me_please_dady = 0;
	while (args && args->data)
	{
		data->index = 1;
		if (args->data[0] == '-')
		{
			while (args->data[data->index] && !data->break_me_please_dady)
			{
				if (args->data[data->index] == 'n')
					data->index++;
				else
					data->break_me_please_dady = 1;
			}
		}
		else
			break ;
		if (data->break_me_please_dady)
			break ;
		data->n_line = 0;
		args = args->next;
	}
	return (args);
}

int	ft_echo(t_node *args, int number_of_arg)
{
	int		i;
	int		n_line;
	t_data	data;

	args = ft_help_echo(args, &data);
	n_line = data.n_line;
	i = 0;
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

// =========================================================================

int	ft_env(void)
{
	t_env	*tmp;

	tmp = g_global.env;
	while (tmp)
	{
		if (tmp->is_equal)
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

// =========================================================================

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

// =========================================================================
