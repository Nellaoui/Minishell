/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:47 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/17 15:55:27 by nelallao         ###   ########.fr       */
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

void	setup_in_redirects(t_node *in_red)
{
	while (in_red != NULL)
	{
		if (access(in_red->data, F_OK) == 0)
		{
			int	fd = open(in_red->data, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else
		{
			dprintf(2, "minishell: %s: No such file or directory\n", in_red->data);
		}
		in_red = in_red->next;
	}
}

void	setup_out_redirects(t_node *out_red)
{
	while (out_red != NULL)
	{
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
	int		len;
	t_node	*current;
	char	**doubleArray;
	int		i;

	i = 0;
	current	= head;
	len = 0;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	doubleArray = (char **)malloc(len * sizeof(char *));
	current = head;
	while (i < len)
	{
		doubleArray[i] = current->data;
		current = current->next;
		i++;
	}
	return (doubleArray);
}

/**********************/
void	exec_cmd(t_node *cmd, char **env)
{
	pid_t	pid;
	char	**paths;
	t_node	*tmp;

	pid = fork();
	if (pid == 0)
	{
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

void	exec_simple_cmd(t_cmd *node, char **env)
{
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

char *get_index(char *string)
{
	int i;

	i = 0;
	while (string[i] && (ft_isalnum(string[i]) || (string[i] == '_')))
		i++;
	return(ft_substr(string, 0, i));
}

int	ft_is_valid(char c)
{
	return ((ft_isalnum(c)) || (c == '_') || (c = '?'));
}

char	*get_value(char *id, t_env *envi)
{
	t_env *tmp;

	tmp = envi;
	// write(1, "X", 1);
	// 	exit(1);
	while (tmp)
	{
		if (ft_strcmp(id, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	get_str_len(char *data, t_env *envi)
{
	int	len;
	int	i;
	char *identifire;
	char *value;

	i = 0;
	len = 0;

	while (data[i])
	{
		if (data[i] == '\'' && ++i)
		{
			while (data[i] && data[i] != '\'')
			{
				len++;
				i++;
			}
		}
		else if (data[i] == '$' && ++i)
		{
			if (ft_is_valid(data[i]) == 0)
				len++;
			else
			{
				identifire = get_index(&data[i]);
				value = get_value(identifire, envi);
				if (identifire[0] == '?' && identifire[1] == '\0')
					value = ft_strdup("42");
				i = i + ft_strlen(identifire);
				len = len + ft_strlen(value);
				// free(value);
				// free(identifire);
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*get_new_string(int str_len, char *data, t_env *envi)
{
	int		len;
	int		i;
	char	*string;
	char	*identifire;
	char	*value;

	string = malloc(str_len + 1);
	i = 0;
	len = 0;
	while (data[i])
	{
		if (data[i] == '\'' && ++i)
		{
			while (data[i] && data[i] != '\'')
			{
				string[len] = data[i];
				len++;
				i++;
			}
		}
		else if (data[i] == '$' && ++i)
		{
			if (ft_is_valid(data[i]) == 0)
			{
				string[len] = data[i];
				len++;
			}
			else
			{
				identifire = get_index(&data[i]);
				value = get_value(identifire, envi);
				if (identifire[0] == '?' && identifire[1] == '\0')
					value = ft_strdup("42");
				i = i + ft_strlen(identifire);
				memcpy(&string[len], value, ft_strlen(value));
				len = len + ft_strlen(value);
				// free(value);
				// free(identifire);
			}
		}
		else
		{
			string[len] = data[i];
			len++;
			i++;
		}
	}
	return (string);
}

char	*get_expanded(char *data, t_env *envi)
{
	char	*string;
	int		str_len;

	str_len = get_str_len(data, envi);
	// printf("len = %d\n", str_len);
	string = get_new_string(str_len, data, envi);
	// printf("str = %s\n", string);
	free(data);
	return (string);
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

void	ft_expension(t_cmd *cmd, t_env *envi)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		ft_mini_expen(tmp->args, envi);
		tmp = tmp->next;
	}
}
// =========================================================================
// this fun() create the nodes
// every node has (key) and (value) and (next)
t_env   *create_node(char *key, char *value)
{
	t_env   *node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = key;
	node->value = value;
	node->next = NULL; // every new node is pointing to the NULL at fisrt
	return (node);
}

// =========================================================================
// this fun() add the new node to the list
// **list this variable pionting to the first node (the had of nodes)
// *new_node this is the new variable wich we create
void	add_node(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	tmp = *list;
	if (*list == NULL) // cuz in first time the list was pointing to the null so taht we give it node
		*list = new_node;
	else
	{
		while (tmp->next) // while the next of tmp not pointing to the null (mzl mafatch akhir node)
			tmp = tmp->next; // so that we give it the next node
		tmp->next = new_node; // ?
	}
}

// =========================================================================

t_env	*ft_setup_env(char **env_main)
{
	t_env	*list; // list of nodes (the head of linked list)
	t_env	*node; // list of nodes
	char	**key_value; // this double pointer hold the key and the value
	int		j;

	list = NULL;
	j = -1;
	while (env_main[++j])
	{
		key_value = ft_split(env_main[j], '='); // here we split the env_main so that the key_value[0]->hold the key and key_value[1]->hold the value
		add_node(&list, create_node(key_value[0], key_value[1])); // in this line i create and add node in the same time
	}
	return (list); // i return the list cuz it's the head of linkedlist.
}

void	ft_display_env(t_env *env)
{
	t_env	*tmp;

	if (env)
	{
	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->key)
			printf("[key : %s:\n", tmp->key);
		if (tmp->value)
			printf(" value %s]\n", tmp->value);
		tmp = tmp->next;
	}
	}
	printf("\n");
}
// /Users/nelallao

void	ft_free_ls(t_node *head)
{
	t_node *current;
	t_node *next;

	current = head;
	while(current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
void	ft_frees_ls(t_env *head)
{
	t_env *current;
	t_env *next;

	current = head;
	while(current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_node	*head;
	t_cmd	*cmd;
	t_env	*envi;
	char	*input;

	head = NULL;
	while (ac && av[0])
	{
		envi = (t_env *)malloc(sizeof(t_env));
		envi = ft_setup_env(env);
		// ft_display_env(envi);
		input = readline("-> Donpha❕ ");
		if (input == NULL || input[0] == '\0')
			continue;
		head = ft_token(input, head);
		ft_type(&head);
		if (ft_syntax_error(input, head))
			continue;
		cmd = ft_insert_link(head);
		// all_display(cmd);
		ft_expension(cmd, envi);
		execution(cmd, env);
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		ft_free_ls(head);
		ft_frees_ls(envi);
		free(input);
		// free(envi);
		// free(envi);
		// free(head);
		// free(cmd);
	}
	return (0);
}
// t_node	*ft_create_node(t_cmd *cmd, t_node *head)
// {
// 	t_node *node;
// 	node = (t_node *)malloc(sizeof )
// 	return (0);
// }
