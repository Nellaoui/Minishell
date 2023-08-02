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

void	ft_initialize(t_token *s)
{
	s->i = 0;
	s->start = 0;
	s->double_quote = 0;
	s->single_quote = 0;
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
	ft_display(cmd->args);
	ft_frees_cmd(cmd);
	ft_free_ls(head);
	free(input);
	// ("ps && leaks minishell");
}

void	ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_node	*head;
	t_cmd	*cmd;
	t_env	*envi;
	char	*input;

	ft_s_env(env);
	while (ac && av[0])
	{
		input = ft_readforfree(input);
		if (!strlen(input))
		{
			free(input);
			continue ;
		}
		head = ft_token(input, head);
		if (ft_syntax_error(input, head))
		{
			free(input);
			ft_free_ls(head);
			continue ;
		}
		cmd = ft_insert_link(head);
		ft_free(cmd, input, env, head);
		// system("leaks -q minishell");
	}
	return (0);
}

// void	all_display(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	int		pipe;

// 	pipe = 1;
// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		printf("--------[command %d]-------\n", pipe);
// 		ft_display(tmp->args);
// 		printf("------>>[out_reds]>>-----\n");
// 		ft_display(tmp->out_reds);
// 		printf("------<<[in_reds]<<-----\n");
// 		ft_display(tmp->in_reds);
// 		printf("------<<[herdoc]<<-----\n");
// 		ft_display(tmp->her_reds);
// 		printf("--------------------------\n");
// 		pipe++;
// 		tmp = tmp->next;
// 	}
// }
