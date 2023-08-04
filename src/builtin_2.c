/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:43:24 by aziyani           #+#    #+#             */
/*   Updated: 2023/08/04 20:29:44 by aziyani          ###   ########.fr       */
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

int	ft_cd_error(char *path, t_env	*tmp)
{
	char *old = getcwd(NULL, 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", ft_strlen("OLDPWD")))
		{
			free(tmp->value);
			tmp->value = old;
			break ;
		}
		tmp = tmp->next;
	}
	if (chdir(path) < 0)
	{
		printf("cd : %s : No such file or directory\n", path);
		g_global.exit_status = 126;
		return (1);
	}
	return (0);
}

int	ft_cd(char *path, t_env *env)
{
	char	*new_path;
	t_env	*tmp;

	tmp = env;
	if (!path)
		path = get_variable_env(&g_global.env, "HOME");
	ft_cd_error(path, tmp);
	
	new_path = getcwd(NULL, 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", ft_strlen("PWD")))
		{
			free(tmp->value);
			tmp->value = new_path;
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

// =========================================================================

void	ft_delet_node(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (*env == NULL)
		return ;
	tmp = *env;
	prev = NULL;
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
		if (ft_strncmp(env->key, str, ft_strlen(str) + 1) == 0)
		{
			ft_delet_node(&g_global.env, env->key);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

// =========================================================================
