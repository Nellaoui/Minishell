/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:56:02 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/25 18:05:33 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_token(char *str, t_node *head)
{
	t_token	*s;

	s = (t_token *)malloc(sizeof(t_token));
	ft_initialize(s, head);
	while (str[s->i])
	{
		if (str[s->i] == '\'' && s->double_quote == 0)
			s->single_quote = !s->single_quote;
		if (str[s->i] == '\"' && s->single_quote == 0)
			s->double_quote = !s->double_quote;
		if (str[s->i] == ' ' && s->double_quote == 0 && s->single_quote == 0)
			ft_splited(str, s, &head);
		if ((str[s->i] == '<' || str[s->i] == '>')
			&& (s->double_quote == 0) && (s->single_quote == 0))
			ft_redrection(str, s, &head);
		if (str[s->i] == '|' && s->double_quote == 0 && s->single_quote == 0)
			ft_pipe(str, s, &head);
		s->i++;
	}
	if (str[s->start] == ' ')
		s->start++;
	if (ft_strlen(&str[s->start]) != 0)
		ft_insert_token(&head, &(str[s->start]));
	free(s);
	return (head);
}

void	ft_splited(char *str, t_token *s, t_node **head)
{
	s->res = ft_subfree(str, s->start, s->i - s->start, s);
	if (ft_strlen(s->res) != 0)
		ft_insert_token(head, s->res);
	s->start = s->i + 1;
}

void	ft_redrection(char *str, t_token *s, t_node **head)
{
	if (((str[s->i] == '<' && str[s->i + 1] == '<')
			|| (str[s->i] == '>' && str[s->i + 1] == '>')))
	{
		s->res = ft_subfree(str, s->start, s->i - s->start, s);
		if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
			ft_insert_token(head, s->res);
		s->res = ft_subfree(str, s->i, 2, s);
		ft_insert_token(head, s->res);
		s->start = s->i + 3;
		s->i = s->i + 2;
	}
	if ((str[s->i] == '<' || str[s->i] == '>'))
		ft_rederct(str, s, head);
}

void	ft_rederct(char *str, t_token *s, t_node **head)
{
	s->res = ft_subfree(str, s->start, s->i - s->start, s);
	if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
		ft_insert_token(head, s->res);
	s->res = ft_subfree(str, s->i, 1, s);
	ft_insert_token(head, s->res);
	s->start = s->i + 1;
}

void	ft_pipe(char *str, t_token *s, t_node **head)
{
	char	*pipe;
	char	*string;

	s->res = ft_subfree(str, s->start, s->i - s->start, s);
	if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
		ft_insert_token(head, s->res);
	string = ft_strdup("|");
	pipe = string;
	free(string);
	ft_insert_token(head, pipe);
	s->start = s->i + 1;
}
