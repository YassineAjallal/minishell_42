/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:09 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/26 22:55:18 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 
#include <stdio.h>
#include <readline/readline.h>
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
	int		exit_code;
}	t_global_info;

typedef struct s_command
{
	char *command_path;
	char option;
	char **cmd_parameter;
	bool built_in;
	bool redirect_in;
	bool redirect_out;
	bool redirect_append;
	bool herdoc;
	char *infile;
	char *outfile;
	char *delemiter;
} t_command;

#endif