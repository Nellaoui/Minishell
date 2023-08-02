/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:37:49 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/30 11:43:41 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void	ft_s_env(char **env)
{
	g_global.env = ft_setup_env(env);
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, SIG_IGN);
}

char	*ft_readforfree(char *input)
{
	char	*string;

	string = readline("-> Donpha❕ ");
	input = ft_strtrim(string, " \t");
	add_history(string);
	free(string);
	if (input == NULL)
	{
		free(input);
		exit(g_global.exit_status);
	}
	return (input);
}
