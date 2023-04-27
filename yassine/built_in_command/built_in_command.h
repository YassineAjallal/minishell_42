/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:43:56 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/27 18:50:01 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_COMMAND_H
#define BUILT_IN_COMMAND_H

#include "../minishell.h"

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

char *ft_pwd(void);
int ft_strlen2d(char **str);
char *multiple_join(char **path, int length);
void	ft_free2d(char **str);

int	ft_unset(char *unset_var, t_env *old_env);
t_env 	*dup_env(char **inherit_env);
void	ft_env(t_env *env);
int get_until_equal(char *str);
char **convert_env_array(t_env *env);

void swap_variable(t_variable *var1, t_variable *var2);
void sort_env_variables(t_env *env);
void export_no_param(t_env *export);
int fill_var_list(t_variable new_var, t_env *env);
int export_normal_var(t_variable new_var, t_global_info *g_info);
#endif