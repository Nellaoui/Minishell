/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:02:42 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/26 09:55:42 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (s[0] == 1 || s[1] == 1)
		return (1);
	return (EXIT_SUCCESS);
}

int	ft_syntax_error(char *str, t_node *head)
{
	if (head->type == PIPE && (head->next != NULL || head->next->data == '\0'))
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		return (1);
	}
	while (head != NULL)
	{
		if ((head->next == NULL) || (head->next && head->next->type == PIPE))
		{
			if (head->type <= HERDOC)
			{
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				return (1);
			}
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

char	*ft_backward(char *str)
{
	int		i;
	int		len;
	char	*string;

	i = 0;
	len = ft_strlen(str);
	if (str[i] == '\'' || str[i] == '"')
		str = ft_substr(str, i + 1, len - 2);
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
