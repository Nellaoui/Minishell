/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:57:50 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/07 12:55:38 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_args *fill_arguments(char **line)
{
    t_args *argument;
    int i;
    
    i = -1;
    while (line[++i])
        ;
    argument = malloc(sizeof(t_cmd) * (i + 1));
    i = -1;
    while (line[++i])
    {
        argument[i].args = ft_strdup(line[i]);
    }
    return (argument);
}

t_cmd   *fill_linked_list_cmd(char *line)
{
    t_cmd   *cmd;
    char **new_line;

    new_line = ft_split(line, ' ');
    cmd = malloc(sizeof(t_cmd));
    cmd->args = fill_arguments(new_line);
    cmd->redir = NULL;
    cmd->next = NULL;
    return (cmd);
}