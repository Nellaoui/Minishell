/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:58 by nelallao          #+#    #+#             */
/*   Updated: 2023/06/07 16:14:20 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>

/*---------libft-----------------*/
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *str);
char	*ft_strchr(const char *scanned, int searched);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, int len);
/*-------------------------------*/
#endif
