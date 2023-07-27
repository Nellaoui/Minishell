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


