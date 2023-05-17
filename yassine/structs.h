/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:28:30 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/17 19:51:22 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <fcntl.h>

typedef struct s_variable
{
	char *name;
	char *value;
} t_variable;

typedef struct s_env
{
	int nb_variables;
	t_variable *variables;
}	t_env;

typedef struct s_global_info
{
	t_env	*environ;
	t_env	*export_env;
	char 	**env_array;
	int		exit_code;
	int		nb_pipe;
	int		old_stdout;
}	t_global_info;

typedef struct s_outfile
{
	char *file;
	bool mode;
}	t_outfile;

typedef struct s_command
{
	int ther;
	char *cmd;
	char *command_path;
	char option;
	char **cmd_parameter;
	bool built_in;
	bool redirect_in;
	bool redirect_out;
	bool herdoc;
	char **infile;
	t_outfile **outfile;
	char **delemiter;
	int herdoc_stdout;
	char **original_input;
	t_global_info *g_info;
} t_command;


char *ambiguous_redirect(char *file, t_global_info *g_info);
char **expand_all_param(t_command *cmd, t_global_info *g_info);
char **split_expander(char *expand_all);
int	ft_len(char *s, char c, int p);
int split_expander_len(char *expand_all);
char *ft_expand(char *string, t_global_info *g_info);
char **strjoin2d_string(char **s1, char *s2);
char **ft_strjoin2d(char **s1, char **s2);
char *expand_var(char *string, t_global_info *g_info);
char *quote_trim(char *str, char c);
int search_in_env(t_env *env, char *string);
#endif