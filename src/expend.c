/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:09:50 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/02 23:42:47 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expension(t_cmd *cmd, t_env *envi)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		ft_mini_expen(tmp->args, envi);
		if (tmp->in_reds)
			ft_mini_expen(tmp->in_reds, envi);
		if (tmp->out_reds)
			ft_mini_expen(tmp->out_reds, envi);
		tmp = tmp->next;
	}
	ft_quote(cmd);
}

void	ft_mini_expen(t_node *node, t_env *envi)
{
	t_node	*tmp;

	tmp = node;
	while (tmp)
	{
		tmp->data = get_expanded(tmp->data, envi);
		tmp = tmp->next;
	}
}

char	*get_expanded(char *data, t_env *envi)
{
	char	*string;
	int		str_len;

	str_len = get_str_len(data, envi);
	string = get_new_string(str_len, data);
	return (string);
}

int	get_str_len(char *data, t_env *envi)
{
	t_token	s;

	s.j = 0;
	s.len = 0;
	while (data[s.j])
	{
		if (data[s.j] == '\'' && ++s.j)
		{
			while (data[s.j] && data[s.j] != '\'')
			{
				s.len++;
				s.j++;
			}
		}
		else if (data[s.j] == '$' && ++s.j)
			ft_help_get_len(&s, data, envi);
		else
		{
			s.len++;
			s.j++;
		}
	}
	return (s.len);
}

void	ft_help_get_len(t_token *s, char *data, t_env *envi)
{
	if (ft_is_valid(data[s->j]) == 0)
		s->len++;
	else
	{
		s->id = get_index(&data[s->j]);
		s->value = get_value(s->id, envi);
		if (!s->value)
		{
			free(s->id);
			return ;
		}
		s->j = s->j + ft_strlen(s->id);
		s->len = s->len + ft_strlen(s->value);
		free(s->id);
	}
}
