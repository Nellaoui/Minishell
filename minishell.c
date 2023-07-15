/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:47 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/15 15:03:36 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize(t_token *s)
{
	s->i = 0;
	s->start = 0;
	s->double_quote = 0;
	s->single_quote = 0;
}

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

	if (head)
	{
	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->data)
			printf("[%s:", tmp->data);
		if (tmp->type)
			printf("%d]\n", tmp->type);
		tmp = tmp->next;
	}
	}
	printf("\n");
}

// void displayreverse(t_node *head)
// {
// 	if (head == NULL)
// 	{
// 		return ;
// 	}
// 	displayReverse(head->next);
// 	printf("[%s]\n",head->data);
// }

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
	ft_initialize(&s);
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
	if (s[0] == 1 ||s[1] == 1)
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
			else if (node->type == HERDOC)
			{
				ft_insert_token_2(&(command->her_reds), ft_strdup(node->next->data), node->type);
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
	return (head_command);
}

void	all_display(t_cmd *cmd)
{
	t_cmd *tmp;
	int pipe;

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
/***************************************************************************/

void	setup_in_redirects(t_node *in_red){
	while (in_red != NULL) {
		if (access(in_red->data, F_OK) == 0) {
			int	fd = open(in_red->data, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else {
			dprintf(2, "minishell: %s: No such file or directory\n", in_red->data);
		}
		in_red = in_red->next;
	}
}

void	setup_out_redirects(t_node *out_red) {
	while (out_red != NULL) {
		int	fd = open(out_red->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		out_red = out_red->next;
	}
}

int	check_cmd(char *cmd)
{
	if (access(cmd, F_OK) < 0)
	{
		dprintf(2, "No Such file: %s\n", cmd);
		exit(126);
	}
	if (access(cmd, X_OK) < 0)
	{
		dprintf(2, "Permissions: %s\n", cmd);
		exit(126);
	}
	return (1);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd[0] == '.')
		if (check_cmd(cmd) == 1)
			return (cmd);
	if (cmd[0] == '/')
	{
		cmd = ft_strchr(cmd, '/');
		if (strrchr(cmd, '/') == NULL)
			return (0);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/*****************************/

char **linked_list_to_array(t_node *head)
{
    int len = 0;
    t_node *current = head;
    while (current != NULL)
    {
        len++;
        current = current->next;
    }

    char **doubleArray = (char **)malloc(len * sizeof(char *));

    current = head;
    for (int i = 0; i < len; i++)
    {
        doubleArray[i] = current->data;
        current = current->next;
    }

    return (doubleArray);
}

/**********************/
void	exec_cmd(t_node *cmd, char **env) {
	pid_t	pid;
	char	**paths;
	t_node *tmp;

	pid = fork();
	if (pid == 0) {

		char *tmp = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin";
		char **paths = ft_split(tmp, ':');
		char **e_cmd = linked_list_to_array(cmd);
		e_cmd[0] = get_cmd(paths, e_cmd[0]);
		// printf("command: %s\n", e_cmd[0]);
		for (int i = 0; e_cmd[i]; i++)
			printf("%s\n", e_cmd[i]);
		execve(e_cmd[0], e_cmd, env);
	}
	else
		wait(NULL);
}

void	exec_simple_cmd(t_cmd *node, char **env) {
	printf("simple command\n");


	if (node->in_reds != NULL) {
		setup_in_redirects(node->in_reds);
	}
	if (node->out_reds != NULL) {
		setup_out_redirects(node->out_reds);
	}
	// if (node-> her_reds) {
	// 	setup_heredoc(node->her_reds);
	// }

	exec_cmd(node->args, env);
}

void	exec_compound_cmd(t_cmd *node) {
	printf("compound command\n");
}

void	execution(t_cmd *head, char **env) {
	t_cmd	*curr;
	size_t	size = 0;

	curr = head;
	while (curr) {
		++size;
		curr = curr->next;
	}

	printf("size--> : [%ld]\n", size);
	curr = head;
	if (size == 1) {
		exec_simple_cmd(curr, env);
	}
	else {
		exec_compound_cmd(curr);
	}
}

int	main(int ac, char **av, char **env)
{
	t_node	*head;
	t_cmd	*cmd;
	char	*input;

	head = NULL;
	while (ac && av[0])
	{
		input = readline("-> Donpha❕ ");
		if (input == NULL || input[0] == '\0')
			continue;
		head = ft_token(input, head);
		ft_type(&head);
		if (ft_syntax_error(input, head))
			continue;
		cmd = ft_insert_link(head);
		// all_display(cmd);
		execution(cmd, env);
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
