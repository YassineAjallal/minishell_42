/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:57:21 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/20 18:01:56 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_pipe(int pipes[][2], int nb_pipe)
{
	int i;
	
	i = 0;
	while (i < nb_pipe)
	{
		if (pipe(pipes[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void close_pipes(int pipes[1][2], int nb_pipe)
{
	int i;
	
	i = 0;
	while (i < nb_pipe)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void ft_strtrim2d(char **param)
{
	char *tmp;
	int i;
	
	i = 0;
	while(param[i])
	{
		tmp = ft_strtrim(param[i], " ");
		if (ft_strlen(tmp) == 0)
		{
			free(tmp);
			tmp = ft_strdup(" ");
		}
		free(param[i]);
		param[i] = tmp;
		i++;
	}
}

int pipes(t_command **cmds, t_global_info *g_info)
{
	pid_t	pid;
	int		pipe_arr[g_info->nb_pipe][2];
	int     pids[g_info->nb_pipe + 1];
	int		i;
	int		dup_stdin;
	int		dup_stdout;
	int 	status;
	int j;

	i = -1;
	search_built_in(cmds[0]);
	if (cmds[0]->built_in == true && g_info->nb_pipe == 0)
	{
		g_info->old_stdout = dup(STDOUT_FILENO);
		cmds[0]->cmd_parameter = expand_all_param(cmds[0], g_info);
		exec_built_in(cmds[0]);
		dup2(g_info->old_stdout, STDOUT_FILENO);
	}
	else
	{	
		if (!init_pipe(pipe_arr, g_info->nb_pipe))
			return (0);
		dup_stdin = 0;
		dup_stdout = pipe_arr[i][1];
		while(++i < g_info->nb_pipe + 1)
		{
			cmds[i]->cmd_parameter = expand_all_param(cmds[i], g_info);
			if (i != 0)
				dup_stdin = pipe_arr[i - 1][0];
			if (i == g_info->nb_pipe)
				dup_stdout = 1;
			else
				dup_stdout = pipe_arr[i][1];
			pid = fork();
			if (pid == 0)
			{
				dup2(dup_stdin, STDIN_FILENO);
				if (cmds[i]->herdoc == false)
				{
					dup2(dup_stdout, STDOUT_FILENO);
					close_pipes(pipe_arr, g_info->nb_pipe);
				}
				else
					cmds[i]->herdoc_stdout = dup_stdout;
				cmd_exec(cmds[i]);
			}
			else
				pids[i] = pid;
			if (cmds[i]->herdoc == true)
				wait(NULL);
		}
		close_pipes(pipe_arr, g_info->nb_pipe);
		i = -1;
		while (++i < g_info->nb_pipe + 1)
			waitpid(pids[i], &status, 0);
		g_info->exit_code = WEXITSTATUS(status);
		// printf("exit code : %d\n", g_info->exit_code);
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	if (ac > 1)
		return (0);
	if (av[1])
		return (0);
	int i;
	char *input;
	char *tmp;
	char **split;
	t_command **cmd;
	t_global_info *g_info;
	cmd = malloc(sizeof(t_command *));
	cmd[0] = malloc(sizeof(t_command));
	g_info = malloc(sizeof(t_global_info));
	g_info->environ = dup_env(env);
	g_info->export_env = dup_env(env);
	g_info->exit_code = 0;
	g_info->env_array = convert_env_array(g_info->environ);
	g_info->nb_pipe = 2;
	while(1)
	{
		input = readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");
		if(!input)
			exit(g_info->exit_code);
		input = ft_strtrim(input, " ");
		if (ft_strlen(input) != 0)
		{
			add_history(input);
			split = lexer(input, g_info);
			if(split != NULL)
			{
				if(syntx_error_a(split, g_info) && syntx_error_b(split, g_info))
				{
					cmd = rmplir_strct(split, g_info);
					pipes(cmd, g_info);				
				}
			}
		}
		else
			g_info->exit_code = 0;
	}
}

// ls | sleep 5 | echo y
// cat << yajallal | wc -l | ls
// readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");