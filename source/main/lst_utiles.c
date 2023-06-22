/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:39:52 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/22 11:14:35 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// =========================================================================
char	*get_key_env(char *env, int *i)
{
	int j;
	int	len;
	char	*key;

	len = *i;
	while (env[++len] && env[len] != '=')
		;
	key = malloc(len + 1);
	j = -1;
	*i = len;
	while (++j < len)
		key[j] = env[j];
	key[j] = 0;
	return (key);
}

// =========================================================================

char	*get_value_env(char *env, int *i)
{
	char	*value;
	int		len;
	int		j;
	
	len = -1;
	j = *i;
	while (env[++len])
		;
	len = len - j;
	value = malloc(len + 1);
	if (!value)
		return (0);
	len = -1;
	while (env[j])
		value[++len] = env[j++];
	value[len] = 0;
	return (value);
}

// =========================================================================

t_env   *create_node(char *key, char *value)
{
	t_env   *node;
	
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
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