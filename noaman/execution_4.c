/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:39:57 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/31 10:36:06 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

t_env	*ft_setup_env(char **env_main)
{
	t_env	*list;
	char	**key_value;
	int		j;
	char	*tmp;
	int		is_qual;

	list = NULL;
	is_qual = 0;
	j = -1;
	while (env_main[++j])
	{
		if (ft_strchr(env_main[j], '=') != NULL)
			is_qual = 1;
		key_value = ft_split(env_main[j], '=');
		tmp = env_main[j] + (ft_strlen(key_value[0]) + 1);
		add_node(&list, create_node(key_value[0], tmp, is_qual));
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

t_env	*create_node(char *key, char *value, int is_qual)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->is_equal = is_qual;
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