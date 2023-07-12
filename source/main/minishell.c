/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:47 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/11 18:15:10 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



// void	ft_insert_token(t_node **head, char *data)
// {
// 	t_node	*new_node;
// 	t_node	*tmp;

// 	new_node = (t_node *)malloc(sizeof(t_node));
// 	new_node->next = NULL;
// 	new_node->previous = NULL;
// 	new_node->data = data;
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 		return ;
// 	}
// 	tmp = *head;
// 	while(tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new_node;
// 	new_node->previous = tmp;

// }

// // t_node	*fill_list(t_node *list)
// // {
// // 	int i = 0;

// // 	while (i < 5)
// // 	{
// // 		ft_insert_token(&list, "test", i);
// // 		i++;
// // 	}
// // 	return (list);
// // }

// void	ft_insert_token2(t_node** head, char* data)
// {
// 	t_node	*new_node;

// 	new_node = (t_node*)malloc(sizeof(t_node));
// 	new_node->data = data;
// 	if (*head == NULL)
// 	{
// 		new_node->next = NULL;
// 	}
// 	else
// 	{
// 		new_node->next = *head;
// 	}

// 	*head = new_node;
// }



// void	ft_display(t_node *head)
// {
// 	t_node	*tmp;

// 	tmp = head;
// 	while (tmp != NULL)
// 	{
// 		printf("[%s:%d]\n", tmp->data, tmp->type);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// }

// void displayReverse(t_node *head)
// {
// 	if (head == NULL)
// 	{
// 		return ;
// 	}
// 	displayReverse(head->next);
// 	printf("[%s]\n",head->data);
// }


// void	ft_splited(char *str, t_token *s, t_node **head)
// {
// 	if (str[s->start] == ' ')
// 		s->start++;
// 	s->res = ft_substr(str, s->start, s->i - s->start);
// 	if (ft_strlen(s->res) != 0 && ft_strlen(s->res) != 1)
// 	{
// 		ft_insert_token(head, s->res);
// 		// printf("me %s\n", s->res);
// 	}
// 	s->start = s->i;
// }

// void	ft_redrection(char *str, t_token *s, t_node **head)
// {
// 	if (((str[s->i] == '<' && str[s->i + 1] == '<')
// 		|| (str[s->i] == '>' && str[s->i + 1] == '>')))
// 	{
// 		s->res = ft_substr(str, s->start, s->i - s->start);
// 		if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
// 			ft_insert_token(head, s->res);
// 		s->res = ft_substr(str, s->i, 2);
// 		ft_insert_token(head, s->res);
// 		s->start = s->i + 2;
// 		s->i = s->i + 2;
// 	}
// 	else if ((str[s->i] == '<'  || str[s->i] == '>'))
// 	{
// 		s->res = ft_substr(str, s->start, s->i - s->start);
// 		if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
// 			ft_insert_token(head, s->res);
// 		s->res = ft_substr(str, s->i, 1);
// 		ft_insert_token(head, s->res);
// 		s->start = s->i + 1;
// 	}
// }

// void	ft_pipe(char *str, t_token *s, t_node **head)
// {
// 	char	*pipe;

// 	s->res = ft_substr(str, s->start, s->i - s->start);
// 	if (ft_strlen(s->res) != 0 && str[s->i - 1] != ' ')
// 		ft_insert_token(head, s->res);
// 	pipe = ft_strdup("|");
// 	ft_insert_token(head, pipe);
// 	s->start = s->i + 1;
// }

// t_node	*ft_token(char *str, t_node *head)
// {
// 	t_token s;

// 	head = NULL;
// 	s.i = 0;
// 	s.start = 0;
// 	s.double_quote = 0;
// 	s.single_quote = 0;
// 	while (str[s.i])
// 	{
// 		if (str[s.i] == '\'' && s.double_quote == 0)
// 			s.single_quote = !s.single_quote;
// 		if (str[s.i] == '\"' && s.single_quote == 0)
// 			s.double_quote = !s.double_quote;
// 		if (str[s.i] == ' ' && s.double_quote == 0 && s.single_quote == 0)
// 			ft_splited(str, &s, &head);
// 		if (str[s.i] == '|' && s.double_quote == 0 && s.single_quote == 0)
// 			ft_pipe(str, &s, &head);
// 		if ((str[s.i] == '<'  || str[s.i] == '>') && (s.double_quote == 0) && (s.single_quote == 0))
// 			ft_redrection(str, &s, &head);
// 		s.i++;
// 	}
// 	if (str[s.start] == ' ')
// 		s.start++;
// 	if (ft_strlen(&str[s.start]) != 0)
// 		ft_insert_token(&head, &(str[s.start]));
// 	return (head);
// }

// void	ft_syntax_error(char *str, t_node *head)
// {

// 	while (head != NULL)
// 	{

// 		head = head->next;
// 	}
// }

// void	ft_type(t_node **head)
// {
// 	t_node	*node;

// 	node = *head;
// 	while (node != NULL)
// 	{
// 		node->type = ARRGUMENT;
// 		if (ft_strcmp(node->data, "|") == 0)
// 			node->type = PIPE;
// 		if (ft_strcmp(node->data, ">") == 0)
// 			node->type = OUT;
// 		if (ft_strcmp(node->data, "<") == 0)
// 			node->type = IN;
// 		if (ft_strcmp(node->data, "<<") == 0)
// 			node->type = HERDOC;
// 		if (ft_strcmp(node->data, ">>") == 0)
// 			node->type = APPEND;
// 		node = node->next;
// 	}
// }
// void ok()
// {
//     char *cmd;
//     char **argv;
//     char **env = NULL;

//     argv = (char **) malloc(3 * sizeof(char *));
//     argv[0] = "/bin/echo";
//     argv[1] = "AAAAAAAAA";
//     execve("/bin/echo", argv, env);
// }

// int	main(void)
// {
// 	t_node	*head;
// 	char	*input;

// 	head = NULL;
// 	char *path = getenv("PATH");
// 	// if (access(path, X_OK))
// 		// ok();
// 	// ok();
// 	while (1)
// 	{
// 		input = readline("-> minishell> ");
// 		// system(input);
// 		// head = ft_token(input, head);
// 		// ft_syntax_error(input, head);
// 		// ft_type(&head);
// 		// ft_display(head);
// 		add_history(input);
// 		// if (ft_strcmp(input, "exit") == 0)
// 		// 	exit(1);
// 		free(input);
// 	}
// }
// // 	// t_node	*list;

// // 	// list = NULL;
// // 	// list = fill_list(list);
// // 	// printf("%s %d\n", list->next->previous->data, list->next->index);
// // 	// while (list)
// // 	// {
// // 	// 	printf("%s %d\n", list->data, list->index);
// // 	// 	list = list->next;
// // 	// }

// // 	return (0);
// // }

// =========================================================================
// env_main variable hold the envairment

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

// =========================================================================

// char	**dup_argument(t_args *args)
// {
// 	char **ptr;
// 	int	i;

// 	i = -1;
// 	while (args[++i].args)
// 		;
// 	ptr = malloc(sizeof(char *) * (i + 1));
// 	if (!ptr)
// 		return (0);
// 	i = -1;
// 	while (args[++i].args)
// 		ptr[i] = ft_strdup(args[i].args);
// 	ptr[i] = 0;
// 	return (ptr);
// }
// =========================================================================

char	*get_path(char *cmd)
{
	t_env *env;
	char	*path;
	char	**last_path;
	env = global.g_env;
	
	while (env)
	{
		if(!ft_strncmp(env->key, "PATH", -1))
			path = env->value;
		env = env->next;
	}
	last_path = ft_split(path, ':');
	int i = -1;
	while (last_path[++i])
	{
		path = ft_strjoin(last_path[i], "/");
		path = ft_strjoin(path, cmd);
		if (!access(path, F_OK))
			return (path);
	}
	return (0);
}

// =========================================================================
// this func() execute the commands and do the redirections.
// word = this variable hold the command or the name of redirection file(which we read or write in it).
// type = this variable hold the redirections like (PIPE, IN, OUT, APPEND, HERDOC, CMD).
// dup2 = this
// access = is a system call take (path and mode=[F_OK]) and check if that path is exist (katchoflk wach dak lfile kayn fdak lpath wla la), if it exist its return (0) if not return (-1)
// fork = is a system call that creates a new process. the new process, called the child process.

// void	execution(t_cmd *cmd,char **env_main)
// {
// 	int pid;
// 	char	**arr;
// 	char	*path;
// 	char	*command;
// 	int i;
// 	int fd[2]; // fd[0] == read_end pipe;  | fd[1] == write_end pipe; 
// 	 i = -1;
// 	while (cmd)
// 	{
// 		if (cmd->type == PIPE)
// 		{
// 			if (pipe(fd) < 0)
// 				perror("minishell :");
// 		}
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (cmd->type == APPEND)
// 			{
// 				int fd = open(cmd->word, O_WRONLY | O_APPEND);
// 				dup2(fd, STDOUT_FILENO);
// 			}
// 			if (cmd->type == OUT)
// 			{
// 				int fd = open(cmd->word, O_WRONLY | O_TRUNC | 0644);
// 				dup2(fd, STDOUT_FILENO);
// 			}
// 			if (cmd->type == IN)
// 			{
// 				if (access(cmd->word, F_OK) == 0)
// 				{
// 					int fd = open(cmd->word, O_RDONLY);
// 					dup2(fd, STDIN_FILENO);
// 				}
// 				else
// 					printf("minishell: %s: No such file or directory\n", cmd->word);
// 			}
// 			if (cmd->type == CMD) // here we execute the commands (ls, cat...)
// 			{
// 				char **arr = ft_split(cmd->word, ' ');
// 				execve(cmd->word, arr, env_main);
// 			}
// 		}
// 		cmd = cmd->next; // here we move to next node which hold the redirection(if it exist).
// 	}
// }

// =========================================================================

void	exec(t_cmd *cmd, char **env)
{
	if (cmd->in_reds)
	{
		int in = open(cmd->in_reds->data, O_RDONLY);
		dup2(in, STDIN_FILENO);
	}
	if (cmd->out_reds)
	{
		int out = open(cmd->out_reds->data, O_RDWR | O_CREAT, 0644);
		dup2(out, STDOUT_FILENO);
	}
	char *c;
	while (cmd->args->data)
	{
		c = ft_strjoin(c, cmd->args->data);
		cmd->args = cmd->args->next;	
	}
	char **spt = ft_split(c, ' ');
	execve(spt[0], spt, env);	
}

int main(int argc, char const *argv[], char **env_main)
{
	int i = 0;
	t_cmd	*head;

	global.g_env = ft_setup_env(env_main);
	// tmp = global.g_env;
	while (1)
	{
		char *line = readline("#-->minishell>");
		// ft_export(&global.g_env, input);
		// ft_export(&global.g_env, "aziyan=loool");
		// ft_env();
		// printf("========\n");
		// ft_export(&global.g_env, "aziyan=toooz");
		// ft_env();
		// ft_export(&global.g_env, "aziyani");
		// ft_env();
		// cmd = fill_linked_list_cmd(line);
		exec(head, env_main);
	}
	return 0;
}

// =========================================================================