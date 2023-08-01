/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:27:57 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/31 12:35:41 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_info	*g_info;

void	sigint_signal(int signal)
{
	(void)signal;
	if (g_info->signal == 0)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_info->exit_code = 1;
	}
	else
	{
		g_info->signal = 0;
		ft_putstr_fd("\n", 1);
	}
}

void	sigquit_signal(int signal)
{
	(void)signal;
	rl_on_new_line();
}

int	main(int ac, char **av, char **env)
{
	t_command		**cmd;

	if (ac > 1 || av[1])
		return (0);
	cmd = NULL;
	g_info = init_g_info(env);
	if (!g_info)
		return (0);
	minishell_readline(g_info, cmd);
	return (0);
}
