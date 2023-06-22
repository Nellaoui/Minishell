/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:48:58 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/19 21:52:10 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// PWD ila kayna flikedlist katprantiha 
// wila makaynach katla3 error

typedef struct struct_env_s
{
	char *key;
	char *value;
	struct struct_env_s *next;
}struct_env;

int	ft_pwd(void)
{
	struct_env *env;

	while (env)
	{
		if (env->key == "PWD")
		{
			printf("%s\n", env->value);
			return (0);
		}
			
		env = env->next;
	}
	return (1);
}