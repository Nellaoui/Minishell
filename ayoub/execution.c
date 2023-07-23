/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:43:16 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/21 18:57:55 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env   *create_node(char *key, char *value)
{
	t_env   *node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
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

void	exec_compound_cmd(t_cmd *node)
{
	printf("compound command\n");
}

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
	// printf("simple command\n");
	if (node->in_reds != NULL)
	{
		setup_in_redirects(node->in_reds);
	}
	if (node->out_reds != NULL)
	{
		setup_out_redirects(node->out_reds);
	}
	// if (node-> her_reds) {
	// 	setup_heredoc(node->her_reds);
	// }
	exec_cmd(node->args, env);
}

void	execution(t_cmd *head, char **env)
{
	t_cmd	*curr;
	size_t	size;

	size = 0;
	curr = head;
	while (curr) {
		++size;
		curr = curr->next;
	}

	// printf("size--> : [%ld]\n", size);
	curr = head;
	if (size == 1)
	{
		exec_simple_cmd(curr, env);
	}
	else {
		exec_compound_cmd(curr);
	}
}

t_env	*ft_setup_env(char **env_main)
{
	t_env	*list; // list of nodes (the head of linked list)
	// t_env	*node; // list of nodes
	char	**key_value; // this double pointer hold the key and the value
	int		j;

	list = NULL;
	j = -1;
	while (env_main[++j])
	{
		key_value = ft_split(env_main[j], '='); // here we split the env_main so that the key_value[0]->hold the key and key_value[1]->hold the value
		add_node(&list, create_node(key_value[0], key_value[1])); // in this line i create and add node in the same time
		// free_arr(key_value);
	}
	return (list); // i return the list cuz it's the head of linkedlist.
}


