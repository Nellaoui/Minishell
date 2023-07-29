/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:39:57 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/29 20:15:13 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

t_env	*ft_setup_env(char **env_main)
{
	t_env	*list;
	char	**key_value;
	int		j;

	list = NULL;
	j = -1;
	while (env_main[++j])
	{
		key_value = ft_split(env_main[j], '=');
		add_node(&list, create_node(key_value[0], key_value[1]));
		free_arr(key_value);
	}
	return (list);
}

// =========================================================================

void	add_node(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	tmp = *list;
	if (*list == NULL)
		*list = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

// =========================================================================

t_env	*create_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

// =========================================================================

void	ft_command(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (tmp)
	{
		tmp = tmp->next;
	}
}

// =========================================================================