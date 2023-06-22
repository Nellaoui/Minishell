/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:05 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/21 17:21:13 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// lina kayna kanprantiha 
// ila ma3ndhach lvalue matprantihach

int	ft_env()
{
	while (global.g_env)
	{
		printf("%s=%s\n", global.g_env->key, global.g_env->value);
		global.g_env = global.g_env->next;
	}
	return (0);
}
