/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:28 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/19 21:52:45 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// l9iti node liratmshha rak ratmsahha
// mal9itihach makatla3 walo

typedef struct struct_env_s
{
	char *key;
	char *value;
	struct struct_env_s *next;
}struct_env;

int	ft_unset(char *str)
{
	struct_env *env;

	while (env)
	{
		if (env->key == str)
		{
			ft_delet_node(env); // dik node li l9ina lkey dyalha kaysawilina dak lstr kanmhiwha mn list
			return (0);
		}
			
		env = env->next;
	}
	return (1);
}