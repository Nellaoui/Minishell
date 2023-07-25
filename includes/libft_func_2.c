/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:39:30 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/25 17:46:26 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;

	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}



int	ft_isalnum(int n)
{
	if ((n >= '0' && n <= '9') || (n >= 'a' && n <= 'z') || (n >= 'A'
			&& n <= 'Z'))
		return (1);
	else
		return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}


