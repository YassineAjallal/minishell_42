/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:17:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/25 10:53:50 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

#include "../structs.h"
# include "../built_in_command/built_in_command.h"

char *extract_var(char *expand_split, char *expand_string, t_global_info *g_info);
char **expand_all_param(t_command *cmd);
t_expand *expand_linked_list(t_expand *head, t_global_info *g_info);
t_expand *ft_expand(char *string);
char *expand_var(char *string, t_global_info *g_info);
int search_in_env(t_env *env, char *string);

char **convert_linked_array(t_expand *head);
char **ft_strjoin2d(char **s1, char **s2);

char *to_lower(char *command);

t_expand *init_node_no_quote(t_expand *node, t_expand *new_node);
t_expand *expand_linked_no_quote(t_expand *node, t_expand *new_node, char *prev_q);

t_expand *init_node_quote(t_expand *node, t_expand *new_node, t_global_info *g_info);
t_expand *expand_linked_quote(t_expand *node, t_expand *new_node, t_global_info *g_info, char *prev);

#endif