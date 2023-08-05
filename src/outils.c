/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:08:01 by nelallao          #+#    #+#             */
/*   Updated: 2023/08/02 23:43:16 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_subfree(char *str, int start, int len)
{
	char	*string;
	char	*res;

	string = ft_substr(str, start, len);
	res = string;
	free(string);
	return (string);
}

int	ft_is_valid(char c)
{
	return ((ft_isalnum(c)) || (c == '_') || (c = '?'));
}

char	*get_index(char *string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (string[i] >= '0' && string[i] <= '9')
	{
		while (string[i] && (string[i] >= '0' && string[i] <= '9'))
			i++;
		j = i;
		while (string[j] && !ft_isdigit(string[i]))
			j++;
		return (ft_substr(string, i, j));
	}
	i = 0;
	if (string[i] && string[i] == '?')
		return (ft_substr(string, 0, i + 1));
	while (string[i] && (ft_isalnum(string[i]) || (string[i] == '?')))
		i++;
	return (ft_substr(string, 0, i));
}

void	free_arr(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

char	*get_value(char *id, t_env *envi)
{
	t_env	*tmp;

	tmp = envi;
	while (tmp)
	{
		if ((ft_strlen(id) == ft_strlen(tmp->key))
			&& (ft_strncmp(id, tmp->key, ft_strlen(tmp->key)) == 0))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}
