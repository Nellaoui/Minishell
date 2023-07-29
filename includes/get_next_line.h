/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:45:44 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/28 16:48:00 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  2002
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*ft_strjoin2(char *s1, char *s2);
char	*get_next_line(int fd);
char	*cline(char *s);
char	*bowl(char *s);

int		ft_strchr2(char *s, int c);

size_t	ft_strlen2(char *s);

#endif
