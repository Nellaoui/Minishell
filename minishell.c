/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:47 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/14 12:30:46 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_insert_token(t_node **head, char *data)
{
	t_node	*new_node;
	t_node	*tmp;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->data = data;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->previous = tmp;
}
void	ft_insert_token_2(t_node **head, char *data, int type)
{
	t_node	*new_node;
	t_node	*tmp;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->data = data;
	new_node->type = type;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->previous = tmp;
}

/*-------------------------------------*/
void	ft_display(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("[%s:%d]\n", tmp->data, tmp->type);
		tmp = tmp->next;
	}
	printf("\n");
}
// void	ft_display_cmd(t_cmd *head)
// {
// 	t_cmd	*tmp;

// 	tmp = head;
// 	while (tmp != NULL)
// 	{
// 		ft_display(tmp->args);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// }

void displayReverse(t_node *head)
{
	if (head == NULL)
	{
		return ;
	}
	displayReverse(head->next);
	printf("[%s]\n",head->data);
}

/*-------------------------------------*/
void	ft_splited(char *str, t_token *s, t_node **head)
{
	if (str[s->start] == ' ')
		s->start++;
	s->res = ft_substr(str, s->start, s->i - s->start);
	if (ft_strlen(s->res) != 0)
		ft_insert_token(head, s->res);
	s->start = s->i;
}

void	ft_redrection(char *str, t_token *s, t_node **head)
{
	if (str[s->start] == ' ')
		s->start++;
	if (((str[s->i] == '<' && str[s->i + 1] == '<')
		|| (str[s->i] == '>' && str[s->i + 1] == '>')))
	{
		s->res = ft_substr(str, s->start, s->i - s->start);
		if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
			ft_insert_token(head, s->res);
		s->res = ft_substr(str, s->i, 2);
		ft_insert_token(head, s->res);
		s->start = s->i + 2;
		s->i = s->i + 2;
	}
	else if ((str[s->i] == '<'  || str[s->i] == '>'))
	{
		s->res = ft_substr(str, s->start, s->i - s->start);
		if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
			ft_insert_token(head, s->res);
		s->res = ft_substr(str, s->i, 1);
		ft_insert_token(head, s->res);
		s->start = s->i + 1;
	}
}

void	ft_pipe(char *str, t_token *s, t_node **head)
{
	char	*pipe;

	s->res = ft_substr(str, s->start, s->i - s->start);
	if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
		ft_insert_token(head, s->res);
	pipe = ft_strdup("|");
	ft_insert_token(head, pipe);
	s->start = s->i + 1;
}

t_node	*ft_token(char *str, t_node *head)
{
	t_token s;

	head = NULL;
	s.i = 0;
	s.start = 0;
	s.double_quote = 0;
	s.single_quote = 0;
	while (str[s.i])
	{
		if (str[s.i] == '\'' && s.double_quote == 0)
			s.single_quote = !s.single_quote;
		if (str[s.i] == '\"' && s.single_quote == 0)
			s.double_quote = !s.double_quote;
		if (str[s.i] == ' ' && s.double_quote == 0 && s.single_quote == 0)
			ft_splited(str, &s, &head);
		if (str[s.i] == '|' && s.double_quote == 0 && s.single_quote == 0)
			ft_pipe(str, &s, &head);
		if ((str[s.i] == '<'  || str[s.i] == '>') && (s.double_quote == 0) && (s.single_quote == 0))
			ft_redrection(str, &s, &head);
		s.i++;
	}
	if (str[s.start] == ' ')
		s.start++;
	if (ft_strlen(&str[s.start]) != 0)
		ft_insert_token(&head, &(str[s.start]));
	return (head);
}

int	ft_check_quotes(char *str)
{
	int	i;
	int	double_quote = 0;
	int	single_quote = 0;
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		if (str[i] == '\"' && single_quote == 0)
			double_quote = !double_quote;
		if (str[i] == '\'' && double_quote == 0)
			s_q++;
		if (str[i] == '"' && single_quote == 0)
			d_q++;
		i++;
	}
	if (s_q == 1 ||d_q == 1)
		return (1);
	return (EXIT_SUCCESS);
}

int	ft_syntax_error(char *str, t_node *head)
{
	if (head->type == PIPE && head->next != NULL)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		return (1);
	}
	while (head != NULL)
	{
		if ((head->next == NULL) || (head->next && head->next->type == PIPE))
			if (head->type <= HERDOC)
			{
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				return (1);
			}
		if (head->type == ARRGUMENT)
			if (ft_check_quotes(head->data) == 1)
			{
				ft_putstr_fd("syntax error: unexpected end of file\n", 2);
				return (1);
			}
		head = head->next;
	}

	return (0);
}

void	ft_type(t_node **head)
{
	t_node	*node;

	node = *head;
	// node->type = 0;
	while (node != NULL)
	{
		node->type = ARRGUMENT;
		if (ft_strcmp(node->data, "|") == 0)
			node->type = PIPE;
		if (ft_strcmp(node->data, ">") == 0)
			node->type = OUT;
		if (ft_strcmp(node->data, "<") == 0)
			node->type = IN;
		if (ft_strcmp(node->data, "<<") == 0)
			node->type = HERDOC;
		if (ft_strcmp(node->data, ">>") == 0)
			node->type = APPEND;
		node = node->next;
	}
}



// }// {echo} {hey} ({>} {out}) (< in) world (>> app) | pwd (<< here)

t_cmd	*ft_lstlast(t_cmd *node)
{
	if (node == NULL)
		return (NULL);
	t_cmd *curr = node;

	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}


t_cmd	*ft_new_node()
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->in_reds = NULL;
	cmd->out_reds = NULL;
	return (cmd);
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
		{
			if (node->type == ARRGUMENT)
				ft_insert_token_2(&(command->args), ft_strdup(node->data), node->type);
			else if (node->type == OUT || node->type == APPEND)
			{
				ft_insert_token_2(&(command->out_reds), ft_strdup(node->next->data), node->type);
				node = node->next;
			}
			else if (node->type == IN)
			{
				ft_insert_token_2(&(command->in_reds), ft_strdup(node->next->data), node->type);
				node = node->next;
			}
		}
		else
		{
			temp_next = ft_new_node();
			command->next = temp_next;
			command = command->next;
		}
		node = node->next;
	}
	// echo hello world | pwd | exit 1
	return (head_command);
}

void	all_display(t_cmd *cmd)
{
		printf("--------[command]-------\n");
		ft_display(cmd->args);
		printf("------>>[out_reds]>>-----\n");
		ft_display(cmd->out_reds);
		printf("------<<[in_reds]<<-----\n");
		ft_display(cmd->in_reds);
		printf("--------------------------\n");
}

int	main(void)
{
	t_node	*head;
	t_cmd	*cmd;
	char	*input;

	head = NULL;
	while (1)
	{
		input = readline("-> Donpha❕ ");
		if (input == NULL || input[0] == '\0')
			continue;
		head = ft_token(input, head);
		ft_type(&head);
		if (ft_syntax_error(input, head))
			continue;
		cmd = ft_insert_link(head);
		all_display(cmd);
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		free(input);
	}
	return (0);
}
// t_node	*ft_create_node(t_cmd *cmd, t_node *head)
// {
// 	t_node *node;
// 	node = (t_node *)malloc(sizeof )
// 	return (0);
// }
