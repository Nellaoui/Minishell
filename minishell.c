/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:34:47 by nelallao          #+#    #+#             */
/*   Updated: 2023/06/08 18:08:46 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_token(char *str)
{
	int		i;
	int		double_quote;
	int		single_quote;
	int		start;
	char	*res;
	// int		end;

	i = 0;
	start = 0;
	double_quote = 0;
	single_quote = 0;
	while(str[i])
	{
		if(str[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		if(str[i] == '\"' && single_quote == 0)
			double_quote = !double_quote;
		// if(double_quote == 0 && single_quote == 0)
		if(str[i] == ' ' && double_quote == 0 && single_quote == 0)
		{
			res = ft_substr(str, start, i - start);
			if (ft_strlen(res) != 0)
				printf("word : %s\n", res);
			start = i + 1;
		}
		if (str[i] == '|' && double_quote == 0 && single_quote == 0)
		{
			
		}
		if (((str[i] == '<' && str[i+1] == '<') || (str[i] == '>' && str[i+1] == '>')) && double_quote == 0 && single_quote == 0)
		{
			printf("redrection %c%c\n", str[i] ,str[i + 1]);
			res = ft_substr(str, start, i - start);
			if (ft_strlen(res) != 0)
				printf("this : %s\n", res);
			start = i + 2;
			i = i +2;
		}
		else if((str[i] == '<'  || str[i] == '>') && double_quote == 0 && single_quote == 0)
		{
			printf("redrection %c\n", str[i]);
			res = ft_substr(str, start, i - start);
			if (ft_strlen(res) != 0)
				printf("symbol : %s\n", res);
			start = i + 1;
			i++;
		}
		i++;
	}
	printf("split : %s\n", &(str[start]));
	return (0);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("-> minishell> ");
		// char	string[40] = "\"hello '  '  world\"  1337 ";
		//
		ft_token(input);
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
			exit(1);
		// printf("%s\n", input);/
		free(input);
	}
	return (0);
}
