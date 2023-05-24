/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:17:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/24 16:41:41 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

#include "../structs.h"
# include "../built_in_command/built_in_command.h"

char *extract_var(char *expand_split, char *expand_string, t_global_info *g_info);
char **expand_all_param(t_command *cmd);
t_expand *ft_expand(char *string);
char **ft_strjoin2d(char **s1, char **s2);
char *expand_var(char *string, t_global_info *g_info);
int search_in_env(t_env *env, char *string);

#endif