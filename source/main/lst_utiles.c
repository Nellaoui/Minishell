/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:39:52 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/23 15:17:37 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// =========================================================================
// this fun() create the nodes
// every node has (key) and (value) and (next)
t_env   *create_node(char *key, char *value)
{
	t_env   *node;
	
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = key;
	node->value = value;
	node->next = NULL; // every new node is pointing to the NULL at fisrt
	return (node);
}

// =========================================================================
// this fun() add the new node to the list
// **list this variable pionting to the first node (the had of nodes)
// *new_node this is the new variable wich we create
void	add_node(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	tmp = *list;
	if (*list == NULL) // cuz in first time the list was pointing to the null so taht we give it node 
		*list = new_node;
	else
	{
		while (tmp->next) // while the next of tmp not pointing to the null (mzl mafatch akhir node)
			tmp = tmp->next; // so that we give it the next node
		tmp->next = new_node; // ?
	}
}

// =========================================================================