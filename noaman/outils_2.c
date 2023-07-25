/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:30:37 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/25 17:59:32 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_ls(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
}
