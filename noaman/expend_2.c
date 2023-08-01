/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:11:49 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/01 19:19:49 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_new_string(int str_len, char *data, t_env *envi)
{
	t_token	*s;
	char	*string;

	s = (t_token *)malloc(sizeof(t_token));
	s->string = calloc(str_len + 1, sizeof(char));
	s->j = 0;
	s->check = 0;
	s->len = 0;
	while (data[s->j])
	{
		if (data[s->j] == '\'' && ++s->j)
			ft_skip(s, data);
		else if (data[s->j] == '$' && ++s->j)
			ft_help_get_str(data, s);
		else
		{
			s->string[s->len] = data[s->j];
			s->len++;
			s->j++;
		}
	}
	if (s->check)
	{
		free(s->string);
		s->string = ft_strdup("$");
	}
	string = ft_strdup(s->string);
	free(s);
	free(data);
	free(s->string);
	return (string);
}
void	ft_help_get_str(char *data, t_token *s)
{
	char	*string;

	s->check = 0;
	if (ft_is_valid(data[s->j]) == 0)
	{
		s->string[s->len] = data[s->j];
		s->len++;
	}
	else
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
			return ;
		}
		s->j = s->j + ft_strlen(s->identifire);
		ft_memcpy(&s->string[s->len], s->value, ft_strlen(s->value));
		s->len = s->len + ft_strlen(s->value);
		free(s->identifire);
		if (s->to_free == 1)
			free(s->value);
	}
}

void	ft_skip(t_token *s, char *data)
{
	while (data[s->j] && data[s->j] != '\'')
	{
		s->string[s->len] = data[s->j];
		s->len++;
		s->j++;
	}
}

void	ft_remove_quote(t_node *head)
{
	t_node	*node;
	int		i;
	char	*string;

	i = 0;
	node = head;
	while (node)
	{
		if (node->data[i] == '\'' || node->data[i] == '"')
		{
			string = ft_backward(node->data);
			free(node->data);
			node->data = string;
			node->quote = 1;
		}
		node = node->next;
	}
}

void	ft_quote(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->args)
			ft_remove_quote(tmp->args);
		if (tmp->out_reds)
			ft_remove_quote(tmp->out_reds);
		if (tmp->in_reds)
			ft_remove_quote(tmp->in_reds);
		if (tmp->her_reds)
			ft_remove_quote(tmp->her_reds);
		tmp = tmp->next;
	}
}
