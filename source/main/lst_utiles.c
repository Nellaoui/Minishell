/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:39:52 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/22 12:16:16 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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