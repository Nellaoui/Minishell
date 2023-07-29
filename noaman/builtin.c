/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:48:52 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/29 15:48:57 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// =========================================================================

char	*get_variable_env(t_env **env, char *var_name)
{
	t_env	*tmp;
	int		i;

	tmp = *env;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->key, ft_strlen(tmp->key) + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_cd(char *path, t_env *env)
{
	DIR	*dir;
	char	*new_path;
	t_env	*tmp;
	
	tmp = env;
	new_path = malloc(PATH_MAX);
	if (!path)
		path = get_variable_env(&g_global.env, "HOME");
	dir = opendir(path);
	if (!dir)
	{
		printf("cd : %s : No such file or directory\n", path);
		return (1);
	}
	else
	{
		if (chdir(path) < 0)
			return (1);
	}
	getcwd(new_path, PATH_MAX);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 4))
		{
			tmp->value = new_path;
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

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

// =========================================================================

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
int is_alpha(char *string) {
	int i;

	i = 0;
	while (string[i]){
		if (!(string[i] >= '0' && string[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}
int ft_exit(t_node *status, char *data)
{
	int	exit_number;
	int i;

	i = 0;
	t_node *x = status;
	while (x)
	{
		i++;
		x = x->next;
	}
	if (i > 2)
	{
		write (2, "exit: too many arguments\n", 21);
		exit (1);
	}
	else
	{
		if (is_alpha(data))
		{
			write(2,"exit: asf: numeric argument required\n", 37);
			exit(255);
		}
		exit_number = ft_atoi(data);
	}
    exit(exit_number);
}

// =========================================================================

int	ft_modify_node(char	*export, char	*key)
{
	if (ft_strncmp(export, key, ft_strlen(key + 1)) == 0)
		return (1);
	return (0);
}

// =========================================================================

int	ft_check_key(char	**key_value)
{
	int	i;

	if (key_value[0][0] != '_' && !ft_isalpha(key_value[0][0]))
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	i = 1;
	while (key_value[0][i])
	{
		if (!(ft_isalnum(key_value[0][i])))
		{
			if (key_value[0][i] != '_')
			{
				ft_putstr_fd("not a valid identifier\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// =========================================================================
//if we not put the value it will segfault so that we should create a
// func() check the value if exist or not

int	ft_export(t_env **export, char *str)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	**key_value;
	int		i;
	int		added;

	added = 0;
	tmp = *export;
	key_value = ft_split(str, '=');
	if (!key_value[1])
	{
		tmp2 = g_global.env;
		while (tmp2)
		{
			printf("declare -x %s=\"%s\"\n", tmp2->key, tmp2->value);
			tmp2 = tmp2->next;
		}
		return (1);
	}
	if (!ft_check_key(key_value))
	{
		i = 0;
		while (tmp)
		{
			if (!ft_strncmp(key_value[0], tmp->key, ft_strlen(tmp->key) + 1))
			{
				tmp->value = ft_strdup(key_value[1]);
				added=1;
				break ;
			}
			tmp = tmp->next;
		}
		if(!added)
		{
			add_node(export, create_node(key_value[0], key_value[1]));
			// free_arr(key_value);
		}
	}
	// free(str);
	return (0);
}

// =========================================================================

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

void	ft_delet_node(t_env **env, char *key)
{
	if (*env == NULL)
	{
        return;
    }

    t_env* tmp = *env;
	t_env *prev = NULL;
	while (tmp && ft_strncmp(tmp->key, key, ft_strlen(key)))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (prev)
		prev->next = tmp->next;
	free(tmp->value);
	free(tmp->key);
	free(tmp);
}

int	ft_unset(char *str)
{
	t_env	*env;

	env = g_global.env;

	while (env)
	{
		if (ft_strncmp(env->key, str, ft_strlen(str) + 1 ) == 0)
		{
			ft_delet_node(&g_global.env, env->key);
			// free(str);
			return (0);
		}
		env = env->next;
	}
	return (1);
}
