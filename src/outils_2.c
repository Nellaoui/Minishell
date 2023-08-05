/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:30:37 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/03 20:18:39 by nelallao         ###   ########.fr       */
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

char	*ft_free_new_str(t_token *s, char *data)
{
	char	*string;

	if (s->check)
	{
		free(s->string);
		s->string = ft_strdup("");
	}
	string = ft_strdup(s->string);
	free(data);
	// free(s->string);
	// free(s);
	return (string);
}

int	ft_hundling(t_token *s, char *data, char *string)
{
	s->identifire = get_index(&data[s->j]);
	s->value = get_value(s->identifire, g_global.env);
	if (s->identifire[0] == '?' && s->identifire[1] == '\0')
	{
		string = ft_itoa(g_global.exit_status);
		s->value = ft_strdup(string);
		s->to_free = 1;
		free(string);
	}
	if (!s->value)
	{
		s->check = 1;
		free(s->identifire);
		return (1);
	}
	s->j = s->j + ft_strlen(s->identifire);
	ft_memcpy(&s->string[s->len], s->value, ft_strlen(s->value));
	s->len = s->len + ft_strlen(s->value);
	free(s->identifire);
	if (s->to_free == 1)
		free(s->value);
	return (0);
}

void	ft_frees_cmd(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;

	current = head;
	while (current)
	{
		next = current->next;
		ft_free_ls(current->args);
		ft_free_ls(current->her_reds);
		ft_free_ls(current->in_reds);
		ft_free_ls(current->out_reds);
		free(current);
		current = next;
	}
}
void	all_display(t_cmd	*cmd)
{
	t_cmd	*tmp;
	int		pipe;

	pipe = 1;
	tmp = cmd;
	while (tmp)
	{
		printf("--------[command %d]-------\n", pipe);
		ft_display(tmp->args);
		printf("------>>[out_reds]>>-----\n");
		ft_display(tmp->out_reds);
		printf("------<<[in_reds]<<-----\n");
		ft_display(tmp->in_reds);
		printf("------<<[herdoc]<<-----\n");
		ft_display(tmp->her_reds);
		printf("--------------------------\n");
		pipe++;
		tmp = tmp->next;
	}
}
