/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:48:52 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/30 09:19:16 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

int	ft_echo(t_node *args, int number_of_arg)
{
	int	i;
	int	n_line;

	i = 0;
	n_line = 1;
	args = args->next;
	while (args && args->data && number_of_arg > 1
		&& ft_strncmp(args->data, "-n", 3) == 0)
	{
		n_line = 0;
		args = args->next;
	}
	while (args && args->data && i <= number_of_arg)
	{
		printf("%s ", args->data);
		i++;
		args = args->next;
	}
	if (n_line)
		printf("\n");
	return (0);
}

// ==========================================================================

int	ft_env(void)
{
	t_env	*tmp;

	tmp = g_global.env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

// =========================================================================

int	ft_modify_node(char	*export, char	*key)
{
	if (ft_strncmp(export, key, ft_strlen(key + 1)) == 0)
		return (1);
	return (0);
}

int	ft_pwd(void)
{
	t_env	*tmp;

	tmp = g_global.env;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->key, 4) == 0)
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

// =========================================================================
//if we not put the value it will segfault so that we should create a
// func() check the value if exist or not

// int	ft_export(t_env **export, char *str)
// {
// 	t_env	*tmp;
// 	t_env	*tmp2;
// 	char	**key_value;
// 	int		i;
// 	int		added;

// 	added = 0;
// 	tmp = *export;
// 	key_value = ft_split(str, '=');
// 	if (!key_value[1])
// 	{
// 		tmp2 = g_global.env;
// 		while (tmp2)
// 		{
// 			printf("declare -x %s=\"%s\"\n", tmp2->key, tmp2->value);
// 			tmp2 = tmp2->next;
// 		}
// 		return (1);
// 	}
// 	if (!ft_check_key(key_value))
// 	{
// 		i = 0;
// 		while (tmp)
// 		{
// 			if (!ft_strncmp(key_value[0], tmp->key, ft_strlen(tmp->key) + 1))
// 			{
// 				tmp->value = ft_strdup(key_value[1]);
// 				added = 1;
// 				break ;
// 			}
// 			tmp = tmp->next;
// 		}
// 		if (!added)
// 		{
// 			add_node(export, create_node(key_value[0], key_value[1]));
// 			free_arr(key_value);
// 		}
// 	}
// 	// free_arr(key_value);
// 	// free(str);
// 	return (0);
// }

// int	ft_cd(char *path, t_env *env)
// {
// 	DIR		*dir;
// 	char	*new_path;
// 	t_env	*tmp;

// 	tmp = env;
// 	new_path = malloc(PATH_MAX);
// 	if (!path)
// 		path = get_variable_env(&g_global.env, "HOME");
// 	dir = opendir(path);
// 	if (!dir)
// 	{
// 		printf("cd : %s : No such file or directory\n", path);
// 		return (1);
// 	}
// 	else
// 	{
// 		if (chdir(path) < 0)
// 			return (1);
// 	}
// 	getcwd(new_path, PATH_MAX);
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->key, "PWD", 4))
// 		{
// 			tmp->value = new_path;
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
