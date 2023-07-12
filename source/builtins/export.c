/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:14 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/11 17:11:08 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// ila 3ndk export whdaha bzf dyal l3ibat li radi tzidhom ldak linked list
// ila 3ndk export a
// ila 3ndk export a=
// ila 3ndk export a=""
// ila deja kan key ytoverwrita ldakchi lidakhal jdid machi yt3awd whdakhr

// =========================================================================

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
	int added=0;

	tmp = *export;
	// while (tmp)
	// {
	// 	printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);  // ila ktbti export bo7dha
	// 	tmp = tmp->next;
	// }
	key_value = ft_split(str, '=');
	if (!ft_check_key(key_value)) // if we not put the value it will segfault so that we should create a func() check the value if exist or not
	{
		i = 0;
		while (tmp)
		{
			// printf("%s vs %s\n", tmp->key,key_value[0]);
			if (!ft_strncmp(key_value[0], tmp->key, ft_strlen(tmp->key) + 1)) // func() return 1 or 0
			{
				tmp->value = ft_strdup(key_value[1]);
				added=1;
				break;
			}
			tmp = tmp->next;
		}
		if(!added)
			add_node(export, create_node(key_value[0], key_value[1]));  // ila 3tak tzid chi node

	}
	return (0);
}

// =========================================================================