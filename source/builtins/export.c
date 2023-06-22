/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:14 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/19 21:51:04 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// ila 3ndk export whdaha bzf dyal l3ibat li radi tzidhom ldak linked list
// ila 3ndk export a
// ila 3ndk export a=
// ila 3ndk export a=""
// 

typedef struct struct_export_s
{
	char *key;
	char *value;
	struct struct_export_s *next;
}struct_export;

int	ft_export(struct_export *export, char *str)
{
    // ila ktbti export bo7dha
	while (export)
	{
		printf("declare -x %s=\"%s\"\n", export->key, export->value);
		export = export->next;
	}
    // ila 3tak tzid chi node
    add_back_node(str);
}