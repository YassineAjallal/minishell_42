/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/11 19:27:51 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void syntax_error(char *input)
{
	char **split_input;
	int i;

	split_input = ft_split(input, ' ');
	i = 0;
	if (!ft_strcmp(split_input[i], "|") || !ft_strcmp(split_input[i], "||"))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		exit(258);
		// return;
	}
	while (split_input[i])
	{
		if (!ft_strcmp(split_input[i], ">") || !ft_strcmp(split_input[i], "<") 
			|| !ft_strcmp(split_input[i], "<<") || !ft_strcmp(split_input[i], ">>") || !ft_strcmp(split_input[i], "|") 
			|| !ft_strcmp(split_input[i], "\"\"") || !ft_strcmp(split_input[i], "\'\'") || !ft_strcmp(split_input[i], "||") )
		{
			i++;
			if (!split_input[i] ||
					!ft_strcmp(split_input[i], ">") || !ft_strcmp(split_input[i], "<") 
					|| !ft_strcmp(split_input[i], "<<") || !ft_strcmp(split_input[i], ">>") || !ft_strcmp(split_input[i], "|")
					|| !ft_strcmp(split_input[i], "\"\"") || !ft_strcmp(split_input[i], "\'\'") || !ft_strcmp(split_input[i], "||"))
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				exit(258);
				// return;
			}
		}	
		i++;	
	}
}

// int main(int ac, char **av, char **env)
// {
// 	char *input ;
// 	while (1)
// 	{
// 		input = readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");
// 		syntax_error(input);
// 	}
// }
