/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:41 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/19 21:46:36 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// ila kayna -n makanprantiwch new line
// ila kayna kanprantiw new line

int	ft_echo(char **echo, int number_of_arg)
{
	int	i;

	i = 0;
	while (i < number_of_arg)
	{
		printf("%s\n", echo[i]);
		i++;
	}
	return (0);
}