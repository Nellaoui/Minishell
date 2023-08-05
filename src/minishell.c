/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:47 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/26 11:56:30 by nelallao         ###   ########.fr       */
/**/
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_initialize(t_token *s)
{
	s = (t_token *)malloc(sizeof(t_token));
	s->i = 0;
	s->start = 0;
	s->double_quote = 0;
	s->single_quote = 0;
	return (s);
}

void	ft_display(t_node *head)
{
	t_node	*tmp;

	if (head)
	{
		tmp = head;
		while (tmp != NULL)
		{
			if (tmp->data)
				printf("['%s':", tmp->data);
			if (tmp->type)
				printf("%d]\n", tmp->type);
			tmp = tmp->next;
		}
	}
	printf("\n");
}

void	ft_free(t_cmd *cmd, char *input, char **env, t_node *head)
{
	ft_expension(cmd, g_global.env);
	ft_execute(cmd, env, g_global.env);
	ft_frees_cmd(cmd);
	ft_free_ls(head);
	free(input);
}

void	ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_node	*head;
	t_cmd	*cmd;
	char	*input;

	ft_s_env(env);
	int stdin = dup(STDIN_FILENO);
	int stdout = dup(STDOUT_FILENO);
	while (ac && av[0])
	{
		input = ft_readforfree(input);
		if (!strlen(input))
		{
			free(input);
			continue ;
		}
		head = ft_token(input, head);
		if (ft_syntax_error(head))
		{
			free(input);
			ft_free_ls(head);
			continue ;
		}
		cmd = ft_insert_link(head);
		env = linked_list_to_array();
		ft_free(cmd, input, env, head);
		dup2(stdin, 0);
		dup2(stdout, 1);
	}
	return (0);
}
