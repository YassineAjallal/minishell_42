/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:30:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/10 17:00:46 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int get_next_space(char *echo_str, int current_pos)
{
	int next_space;
	next_space = 0;

	while(echo_str[current_pos] != ' ' && echo_str[current_pos])
	{
		next_space++;
		current_pos++;
	}
	return (next_space);
}

int check_var_in_env(char *env_var, int var_length, char **env)
{
	int i;
	
	i = 0;
	while(env[i])
	{
		if (ft_strncmp(env_var, env[i], var_length) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void ft_echo(char *echo_str, char **env)
{
	int i;
	int next_space;
	int var_index_in_env;
	i = 0;

	while(echo_str[i])
	{
		if (echo_str[i] == '$')
		{
			next_space = get_next_space(echo_str, i + 1);
			var_index_in_env = check_var_in_env(echo_str + i + 1, next_space, env);
			if (var_index_in_env >= 0)
				ft_putstr_fd(env[var_index_in_env] + next_space + 1, 1);
			i = i + next_space + 1;
			while(echo_str[i] == ' ' && echo_str[i])
				i++;
		}
		if (echo_str[i])
			ft_putchar_fd(echo_str[i], 1);
		i++;
	}
	printf("\n");
}

int main(int argc, char const *argv[], char **env)
{
	ft_echo("yassine $HOME", env);
	return 0;
}
