/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inserting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:59:38 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/29 19:33:18 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_insert_token(t_node **head, char *data)
{
	t_node	*new_node;
	t_node	*tmp;

	if ((ft_strlen(data) == 1) && data[0] == ' ' )
		return ;
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->next = NULL;
	new_node->data = ft_strdup(data);
	new_node->type = 0;
	new_node->quote = 0;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	// free(new_node->data);
}

void	ft_insert_token_2(t_node **head, char *data, int type)
{
	t_node	*new_node;
	t_node	*tmp;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->data = ft_strdup(data);
	new_node->type = type;
	if (*head == NULL)
	{
		*head = new_node;
		free(data);
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	free(data);
}

t_node	*ft_inserting(t_cmd *command, t_node *node)
{
	if (node->type == ARRGUMENT)
		ft_insert_token_2(&(command->args), ft_strdup(node->data), node->type);
	else if (node->type == OUT || node->type == APPEND)
	{
		ft_insert_token_2(&(command->out_reds),
			ft_strdup(node->next->data), node->type);
		node = node->next;
	}
	else if (node->type == IN)
	{
		ft_insert_token_2(&(command->in_reds),
			ft_strdup(node->next->data), node->type);
		node = node->next;
	}
	else if (node->type == HERDOC)
	{
		ft_insert_token_2(&(command->her_reds),
			ft_strdup(node->next->data), node->type);
		node = node->next;
	}
	return (node);
}

t_cmd	*ft_insert_link(t_node *head)
{
	t_node	*node;
	t_cmd	*command;
	t_cmd	*head_command;
	t_cmd	*temp_next;

	head_command = ft_new_node();
	command = head_command;
	node = head;
	while (node)
	{
		if (node->type != PIPE)
			node = ft_inserting(command, node);
		else
		{
			temp_next = ft_new_node();
			command->next = temp_next;
			command = command->next;
		}
		node = node->next;
	}
	return (head_command);
}

void	ft_type(t_node **head)
{
	t_node	*node;

	node = *head;
	while (node != NULL)
	{
		node->type = ARRGUMENT;
		if (ft_strncmp(node->data, "|", 2) == 0)
			node->type = PIPE;
		if (ft_strncmp(node->data, ">", 2) == 0)
			node->type = OUT;
		if (ft_strncmp(node->data, "<", 2) == 0)
			node->type = IN;
		if (ft_strncmp(node->data, "<<", 3) == 0)
			node->type = HERDOC;
		if (ft_strncmp(node->data, ">>", 3) == 0)
			node->type = APPEND;
		node = node->next;
	}
}
