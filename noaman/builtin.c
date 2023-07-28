// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtin.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/26 18:48:52 by nelallao          #+#    #+#             */
// /*   Updated: 2023/07/27 10:50:38 by nelallao         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// // ila drna cd lchi blasa makaynach
// // cd lblasa kayna katkhdm 3adi
// // drti cd wmakaynach lHOME
// // change env pwd and old pwd

// int	ft_cd(char *path)
// {
// 	DIR *dir;

// 	dir = opendir(path);
// 	if (!dir)
// 		return(1);
// 	else
// 	{
// 		if (chdir(path) < 0)
// 			return (1);
// 	}
// 	return (0);
// }

// // ila kayna -n makanprantiwch new line
// // ila kayna kanprantiw new line

// int	ft_echo(char **echo, int number_of_arg)
// {
// 	int	i;

// 	i = 0;
// 	while (i < number_of_arg)
// 	{
// 		printf("%s\n", echo[i]);
// 		i++;
// 	}
// 	return (0);
// }

// // lina kayna kanprantiha
// // ila ma3ndhach lvalue matprantihach

// int	ft_env()
// {
// 	t_env	*tmp;
// 	tmp = g_global.env;
// 	while (tmp)
// 	{
// 		printf("%s=%s\n", tmp->key, tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int ft_exit(int status)
// {
//     exit(status);
// }

// // ila 3ndk export whdaha bzf dyal l3ibat li radi tzidhom ldak linked list
// // ila 3ndk export a
// // ila 3ndk export a=
// // ila 3ndk export a=""
// // ila deja kan key ytoverwrita ldakchi lidakhal jdid machi yt3awd whdakhr

// // =========================================================================

// int	ft_modify_node(char	*export, char	*key)
// {
// 	if (ft_strncmp(export, key, ft_strlen(key + 1)) == 0)
// 		return (1);
// 	return (0);
// }

// // =========================================================================

// int	ft_check_key(char	**key_value)
// {
// 	int	i;

// 	if (key_value[0][0] != '_' && !ft_isalpha(key_value[0][0]))
// 	{
// 		ft_putstr_fd("not a valid identifier\n", 2);
// 		return (1);
// 	}
// 	i = 1;
// 	while (key_value[0][i])
// 	{
// 		if (!(ft_isalnum(key_value[0][i])))
// 		{
// 			if (key_value[0][i] != '_')
// 			{
// 				ft_putstr_fd("not a valid identifier\n", 2);
// 				return (1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// // =========================================================================
// //if we not put the value it will segfault so that we should create a func() check the value if exist or not

// int	ft_export(t_env **export, char *str)
// {
// 	t_env	*tmp;
// 	char	**key_value;
// 	int		i;
// 	int		added;

// 	added = 0;
// 	tmp = *export;
// 	key_value = ft_split(str, '=');
// 	if (!ft_check_key(key_value)) // if we not put the value it will segfault so that we should create a func() check the value if exist or not
// 	{
// 		i = 0;
// 		while (tmp)
// 		{
// 			if (!ft_strncmp(key_value[0], tmp->key, ft_strlen(tmp->key) + 1)) // func() return 1 or 0
// 			{
// 				tmp->value = ft_strdup(key_value[1]);
// 				added=1;
// 				break;
// 			}
// 			tmp = tmp->next;
// 		}
// 		if(!added)
// 			add_node(export, create_node(key_value[0], key_value[1]));
// 	}
// 	return (0);
// }

// // PWD ila kayna flikedlist katprantiha
// // wila makaynach katla3 error
// /*
// typedef struct struct_env_s
// {
// 	char *key;
// 	char *value;
// 	struct struct_env_s *next;
// }struct_env;
// */

// // int	ft_pwd(void)
// // {
// // 	t_env *env;

// // 	env = g_global.env;
// // 	while (env)
// // 	{
// // 		if (env->key == "PWD")
// // 		{
// // 			printf("%s\n", env->value);
// // 			return (0);
// // 		}

// // 		env = env->next;
// // 	}
// // 	return (1);
// // }

// // l9iti node liratmshha rak ratmsahha
// // mal9itihach makatla3 walo

// /*
// typedef struct struct_env_s
// {
// 	char *key;
// 	char *value;
// 	struct struct_env_s *next;
// }struct_env;
// */
// int	ft_unset(char *str)
// {
// 	t_env *env;

// 	env = g_global.env;
// 	while (env)
// 	{
// 		if (env->key == str)
// 		{
// 			ft_delet_node(env); // dik node li l9ina lkey dyalha kaysawilina dak lstr kanmhiwha mn list
// 			return (0);
// 		}
// 		env = env->next;
// 	}
// 	return (1);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:48:52 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/27 13:37:12 by aziyani          ###   ########.fr       */
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
		if (!ft_strncmp(var_name, tmp->key, ft_strlen(tmp->key) + 1)) // func() return 1 or 0
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

// ila drna cd lchi blasa makaynach
// cd lblasa kayna katkhdm 3adi
// drti cd wmakaynach lHOME
// change env pwd and old pwd

int	ft_cd(char *path)
{
	DIR *dir;
	getcwd();
	if (!path)
		path = get_variable_env(&g_global.env, "HOME");
	printf("%s\n",path);
	dir = opendir(path);
	if (!dir)
	{
		printf("cd : %s : No such file or directory\n", path);
		return(1);
	}
	else
	{		if (chdir(path) < 0)
				return (1);
	}
	return (0);
}

// ila kayna -n makanprantiwch new line
// ila kayna kanprantiw new line

int	ft_echo(t_node *args, int number_of_arg)
{
	int	i;
	int	n_line;

	i = 0;
	n_line = 1;
	args = args->next;
	while (args && args->data && number_of_arg > 1 && ft_strncmp(args->data, "-n", 3) == 0)
	{
		n_line = 0;
		args = args->next;
	}
	// args = args->next;
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

// lina kayna kanprantiha
// ila ma3ndhach lvalue matprantihach

int	ft_env()
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
// if you have more than one argument -> no exit just print error
// if you put alphabet not numbers -> exit with print error
// if you put exit only -> exit with 0

int ft_exit(char *status)
{
	int	exit_number;

	exit_number = ft_atoi(status);
    exit((char) status);
}

// =========================================================================

// ila 3ndk export whdaha bzf dyal l3ibat li radi tzidhom ldak linked list
// ila 3ndk export a
// ila 3ndk export a=
// ila 3ndk export a=""
// ila deja kan key ytoverwrita ldakchi lidakhal jdid machi yt3awd whdakhr

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
//if we not put the value it will segfault so that we should create a func() check the value if exist or not

int	ft_export(t_env **export, char *str)
{
	t_env	*tmp;
	char	**key_value;
	int		i;
	int		added;

	added = 0;
	tmp = *export;
	key_value = ft_split(str, '=');
	if (!ft_check_key(key_value)) // if we not put the value it will segfault so that we should create a func() check the value if exist or not
	{
		i = 0;
		while (tmp)
		{
			if (!ft_strncmp(key_value[0], tmp->key, ft_strlen(tmp->key) + 1)) // func() return 1 or 0
			{
				tmp->value = ft_strdup(key_value[1]);
				added = 1;
				break;
			}
			tmp = tmp->next;
		}
		if(!added)
			add_node(export, create_node(key_value[0], key_value[1]));
	}
	return (0);
}

// =========================================================================

// PWD ila kayna flikedlist katprantiha
// wila makaynach katla3 error

int	ft_pwd(void)
{
	t_env	*tmp;

	tmp = g_global.env;
	while (tmp)
	{
		if (!strncmp("PWD", tmp->key, 4))
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
// =========================================================================
// l9iti node liratmshha rak ratmsahha
// mal9itihach makatla3 walo

void	ft_delet_node(t_env **env)
{
	if (*env == NULL) {
        return;  // Empty list, nothing to delete
    }

    t_env* tmp = *env;  // Store the head node
    *env= (*env)->next;  // Change the head to the next node
    free(tmp);
}

int	ft_unset(char *str)
{
	t_env	*env;

	env = g_global.env;
	while (env)
	{
		if (ft_strncmp(env->key, str, ft_strlen(str)) == 0)
		{
			ft_delet_node(&env); // dik node li l9ina lkey dyalha kaysawilina dak lstr kanmhiwha mn list
			return (0);
		}
		env = env->next;
	}
	return (1);
}

// =========================================================================


