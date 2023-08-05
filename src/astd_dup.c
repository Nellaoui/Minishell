/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astd_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:21:29 by aziyani           #+#    #+#             */
/*   Updated: 2023/08/05 23:32:34 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_help_std_dup(char **env)
{
	ft_s_env(env);
	g_global.s_in = dup(STDIN_FILENO);
	g_global.s_out = dup(STDOUT_FILENO);
}

// ==========================================================================

void	ft_help_std(void)
{
	dup2(g_global.s_in, 0);
	dup2(g_global.s_out, 1);
}

// ==========================================================================

void	check_and_set_vr(t_env **export, char **e_cmd)
{
	char	**key_value;
	int		is_qual;
	int		k;

	k = 1;
	is_qual = 0;
	while (e_cmd[k])
	{
		if (e_cmd[k][0])
		{
			if (ft_strchr(e_cmd[k], '=') != NULL)
				is_qual = 1;
			key_value = ft_split(e_cmd[k], '=');
			e_cmd[k] = e_cmd[k] + (ft_strlen(key_value[0]) + 1);
			if (!ft_check_key(key_value[0]))
				add_env_variable(export, key_value[0], e_cmd[k], is_qual);
			else
				g_global.exit_status = 1;
			free_arr(key_value);
		}
		k++;
	}
}
