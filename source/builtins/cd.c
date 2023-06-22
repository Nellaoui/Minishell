/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:48:48 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/21 16:23:14 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 
#include <dirent.h>
// ila drna cd lchi blasa makaynach 
// cd lblasa kayna katkhdm 3adi
// drti cd wmakaynach lHOME
// change env pwd and old pwd

int	ft_cd(char *path)
{
	DIR *dir;
	
	dir = opendir(path);
	if (!dir)
		return(1);
	else
	{
		if (chdir(path) < 0)
		{
			return (1);
		}
	}
	return (0);
}
