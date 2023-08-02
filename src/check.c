/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:02:42 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/02 23:41:26 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_impair(int s, int d)
{
	if ((s % 2 != 0) || (d % 2 != 0))
		return (1);
	return (0);
}

int	ft_check_quotes(char *str)
{
	int	i;
	int	quote[2];
	int	s[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	s[0] = 0;
	s[1] = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote[0] == 0)
			quote[1] = !quote[1];
		if (str[i] == '\"' && quote[1] == 0)
			quote[0] = !quote[0];
		if (str[i] == '\'' && quote[0] == 0)
			s[0]++;
		if (str[i] == '"' && quote[1] == 0)
			s[1]++;
		i++;
	}
	if (s[0] == 1 || s[1] == 1 || ft_impair(s[0], s[1]))
		return (1);
	return (EXIT_SUCCESS);
}

int	ft_syntax_error(t_node *head)
{
	if (head->type == PIPE && head->next == NULL)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		return (1);
	}
	while (head != NULL)
	{
		if ((head->next == NULL) || (head->next && head->next->type == PIPE))
		{
			if (head->type <= HERDOC)
				return (ft_putstr_fd("error near unexpected token\n", 2), 1);
		}
		if (head->type == ARRGUMENT)
		{
			if (ft_check_quotes(head->data) == 1)
				return (ft_putstr_fd("syntax error: unexpected end of file\n", 2)
					, 1);
		}
		head = head->next;
	}
	return (0);
}

char	*ft_if_remove(char *data, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] && data[i] == '\'' && ++i)
		{
			while (data[i] && data[i] != '\'')
				str[j++] = data[i++];
			i++;
		}
		else if (data[i] && data[i] == '\"' && ++i)
		{
			while (data[i] && data[i] != '\"')
				str[j++] = data[i++];
			i++;
		}
		else
			str[j++] = data[i++];
	}
	str[j] = '\0';
	return (str);
}

t_cmd	*ft_new_node(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->in_reds = NULL;
	cmd->out_reds = NULL;
	cmd->her_reds = NULL;
	return (cmd);
}
