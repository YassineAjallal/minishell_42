/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:27:57 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 15:58:55 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_info	*init_g_info(char **env)
{
	t_global_info	*g_info;

	g_info = malloc(sizeof(t_global_info));
	if (!g_info)
		return (NULL);
	g_info->environ = dup_env(env);
	g_info->export_env = dup_env(env);
	g_info->exit_code = 0;
	g_info->env_array = convert_env_array(g_info->environ);
	g_info->nb_pipe = 0;
	return (g_info);
}

void	run_command(char *input, t_global_info *g_info, t_command **cmd)
{
	char	**split;

	add_history(input);
	split = lexer(input, g_info);
	if (split != NULL)
	{
		if (syntx_error_a(split, g_info) && syntx_error_b(split, g_info))
		{
			cmd = rmplir_strct(split, g_info);
			if (!pipes(cmd, g_info))
				exit(EXIT_FAILURE);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	char			*input;
	char			**split;
	t_command		**cmd;
	char			*tmp;
	t_global_info	*g_info;

	if (ac > 1)
		return (0);
	g_info = init_g_info(env);
	if (!g_info)
		return (0);
	while (1)
	{
		input = readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");
		if (!input)
			exit(g_info->exit_code);
		tmp = ft_strtrim(input, " ");
		free(input);
		input = tmp;
		if (ft_strlen(input) != 0)
		{
			
			run_command(input, g_info, cmd);
		}
		else
			g_info->exit_code = 0;
		// system("leaks minishell");
	}
}

// handle $$
