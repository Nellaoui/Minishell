/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:56:02 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/03 18:32:32 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_token(char *str, t_node *head)
{
	t_token	*s;

	s = NULL;
	head = NULL;
	s = ft_initialize(s);
	while (str[s->i])
	{
		if (str[s->i] == '\'' && s->double_quote == 0)
			s->single_quote = !s->single_quote;
		if (str[s->i] == '\"' && s->single_quote == 0)
			s->double_quote = !s->double_quote;
		if ((str[s->i] == ' ' || str[s->i] == '\t')
			&& s->double_quote == 0 && s->single_quote == 0)
			ft_splited(str, s, &head);
		if ((str[s->i] == '<' || str[s->i] == '>')
			&& (s->double_quote == 0) && (s->single_quote == 0))
			ft_redrection(str, s, &head);
		if (str[s->i] == '|' && s->double_quote == 0 && s->single_quote == 0)
			ft_pipe(str, s, &head);
		s->i++;
	}
	if (ft_strlen(&str[s->start]) != 0)
	{
		if (str[s->start] == ' ' || str[s->start] == '\t')
			s->start++;
		ft_insert_token(&head, &(str[s->start]));
	}
	ft_type(&head, s);
	return (head);
}

void	ft_splited(char *str, t_token *s, t_node **head)
{
	s->res = ft_subfree(str, s->start, s->i - s->start);
	if (ft_strlen(s->res) != 0)
		ft_insert_token(head, s->res);
	s->start = s->i + 1;
}

void	ft_redrection(char *str, t_token *s, t_node **head)
{
	if (((str[s->i] == '<' && str[s->i + 1] == '<')
			|| (str[s->i] == '>' && str[s->i + 1] == '>')))
	{
		s->res = ft_subfree(str, s->start, s->i - s->start);
		if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
			ft_insert_token(head, s->res);
		s->res = ft_subfree(str, s->i, 2);
		ft_insert_token(head, s->res);
		s->start = s->i + 2;
		s->i = s->i + 2;
		
	}
	if ((str[s->i] == '<' || str[s->i] == '>'))
		ft_rederct(str, s, head);
}

void	ft_rederct(char *str, t_token *s, t_node **head)
{
	s->res = ft_subfree(str, s->start, s->i - s->start);
	if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
		ft_insert_token(head, s->res);
	s->res = ft_subfree(str, s->i, 1);
	ft_insert_token(head, s->res);
	s->start = s->i + 1;
}

void	ft_pipe(char *str, t_token *s, t_node **head)
{
	s->res = ft_subfree(str, s->start, s->i - s->start);
	if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
		ft_insert_token(head, s->res);
	ft_insert_token(head, "|");
	s->start = s->i + 1;
}
