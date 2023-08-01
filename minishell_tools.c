/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:48:10 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/31 11:27:52 by yajallal         ###   ########.fr       */
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
	g_info->signal = 0;
	g_info->heredoc_exit = 0;
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
			{
				ft_malloc(0, 0);
				free_infos(g_info);
				exit(EXIT_FAILURE);
			}
		}
	}
}

void	minishell_readline(t_global_info *g_info, t_command **cmd)
{
	char	*tmp;
	char	*input;

	while (1)
	{
		signal(SIGINT, sigint_signal);
		signal(SIGQUIT, sigquit_signal);
		input = readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");
		tmp = input;
		if (!input)
		{
			if (g_info)
				free_infos(g_info);
			exit(g_info->exit_code);
		}
		input = ft_strtrim(input, " \t");
		free(tmp);
		if (ft_strlen(input) != 0)
			run_command(input, g_info, cmd);
		else
			g_info->exit_code = 0;
	}
}
