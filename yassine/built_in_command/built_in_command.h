/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:43:56 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/16 19:56:36 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_COMMAND_H
#define BUILT_IN_COMMAND_H

#include "../structs.h"

// typedef struct s_variable
// {
// 	char *name;
// 	char *value;
// } t_variable;

// typedef struct s_env
// {
// 	int nb_variables;
// 	t_variable *variables;
// }	t_env;

int ft_cd(t_command *cmd);
void ft_pwd(t_command *cmd);
int ft_strlen2d(char **str);
char *multiple_join(char **path, int length);
void	ft_free2d(char **str);

int	unset_one_var(char *unset_var, t_env *old_env);
t_env 	*dup_env(char **inherit_env);
void	ft_env(t_command *cmd);
int get_until_equal(char *str);
char **convert_env_array(t_env *env);

void swap_variable(t_variable *var1, t_variable *var2);
void sort_env_variables(t_env *env);
void export_no_param(t_command *cmd);
int fill_var_list(t_variable new_var, t_env *env);
int export_normal_var(t_variable new_var, t_global_info *g_info);
int already_exist(char *name, t_env *env);

void ft_echo(t_command *cmd);
int ft_unset(t_command *cmd);

int search_env(t_env *env, char *to_search, int *var_pos);
int ft_export(t_command *cmd);

void	ft_perror(int fd, char *s, char *str);
int ft_exit(t_command *cmd);
#endif