/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:47 by nelallao          #+#    #+#             */
/*   Updated: 2023/06/22 13:18:00 by aziyani          ###   ########.fr       */
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

// // int	main(void)
// // {
// // 	t_node	*head;
// // 	char	*input;

// // 	head = NULL;
// // 	char *path = getenv("PATH");
// // 	// if (access(path, X_OK))
// // 		// ok();
// // 	// ok();
// // 	while (1)
// // 	{
// // 		input = readline("-> minishell> ");
// // 		// system(input);
// // 		head = ft_token(input, head);
// // 		ft_syntax_error(input, head);
// // 		ft_type(&head);
// // 		ft_display(head);
// // 		add_history(input);
// // 		if (ft_strcmp(input, "exit") == 0)
// // 			exit(1);
// // 		free(input);
// // 	}
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

t_env	*ft_setup_env(char **env_main)
{
	t_env	*list;// list of nodes (the head of linked list)
	t_env	*node;
	char	**key_value;
	int		j;

	list = NULL;
	j = -1;
	while (env_main[++j])
	{
		key_value = ft_split(env_main[j], '=');
		add_node(&list, create_node(key_value[0], key_value[1]));
	}
	return (list);
}

// =========================================================================

int main(int argc, char const *argv[], char **env_main)
{
	int i = 0;
	t_env	*tmp;

	
	global.g_env = ft_setup_env(env_main);
	tmp = global.g_env;
	ft_export(&global.g_env, "#aziyani=nasima");
	// ft_env();
	return 0;
}

// =========================================================================