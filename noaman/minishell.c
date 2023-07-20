/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:47 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/20 18:53:58 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			{
				ft_insert_token_2(&(command->args), ft_strdup(node->data), node->type);
			}
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
			// ft_give_list(node, command);
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

void	ft_give_list(t_node *node, t_cmd *command)
{
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








/*****************************/



/**********************/







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
	while (tmp)
	{
		if (ft_strcmp(id, tmp->key) == 0)
		{
			return (tmp->value);
		}
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
				// write(1, "X", 1);
				identifire = get_index(&data[i]);
				value = get_value(identifire, envi);
				// printf("%s\n", value);
				// exit(1);
				if (identifire[0] == '?' && identifire[1] == '\0')
					value = ft_strdup("42");
				i = i + ft_strlen(identifire);
				len = len + ft_strlen(value);
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

void	ft_skip(t_token *s, char *data)
{
	while (data[s->i] && data[s->i] != '\'')
	{
		s->string[s->len] = data[s->i];
		s->len++;
		s->i++;
	}
}

char	*get_new_string(int str_len, char *data, t_env *envi)
{
	t_token s;

	s.string = malloc(str_len + 1);
	s.j = 0;
	s.len = 0;
	while (data[s.j])
	{
		if (data[s.j] == '\'' && ++s.j)
			ft_skip(&s, data);
		else if (data[s.j] == '$' && ++s.j)
		{
			if (ft_is_valid(data[s.j]) == 0)
			{
				s.string[s.len] = data[s.j];
				s.len++;
			}
			else
			{
				s.identifire = get_index(&data[s.j]);
				s.value = get_value(s.identifire, envi);
				// printf("%s\n", s.value);
				// exit(1);
				if (s.identifire[0] == '?' && s.identifire[1] == '\0')
					s.value = ft_strdup("42");
				s.j = s.j + ft_strlen(s.identifire);
				memcpy(&s.string[s.len], s.value, ft_strlen(s.value));
				s.len = s.len + ft_strlen(s.value);
			}
		}
		else
		{
			s.string[s.len] = data[s.j];
			s.len++;
			s.j++;
		}
	}
	return (s.string);
}

char	*get_expanded(char *data, t_env *envi)
{
	char	*string;
	int		str_len;

	str_len = get_str_len(data, envi);
	string = get_new_string(str_len, data, envi);
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
// =========================================================================

void free_arr(char **s)
{
	int i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
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
		// free(current->data);
		free(current);
		current = next;
	}
}
void	ft_free_env(t_env *head)
{
	t_env *current;
	t_env *next;

	current = head;
	while(current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	ft_frees_cmd(t_cmd *head)
{
	t_cmd *current;
	t_cmd *next;

	current = head;
	while(current)
	{
		next = current->next;
		free(current->args);
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
		// envi = (t_env *)malloc(sizeof(t_env));
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
		ft_expension(cmd, envi);
		all_display(cmd);
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
	}
	return (0);
}
// t_node	*ft_create_node(t_cmd *cmd, t_node *head)
// {
// 	t_node *node;
// 	node = (t_node *)malloc(sizeof )
// 	return (0);
// }
