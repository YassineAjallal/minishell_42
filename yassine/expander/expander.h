/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:17:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/25 11:55:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../structs.h"
# include "../built_in_command/built_in_command.h"

/*-----expand_lst.c-----*/
t_expand	*init_node(t_expand *node, t_expand *new_node, \
t_global_info *g_info, char **prev);
t_expand	*expand_nodes(t_expand *node, t_expand *new_node, \
t_global_info *g_info, char *prev);
t_expand	*expand_linked_list(t_expand *head, t_global_info *g_info);

/*-----expand_no_quote.c-----*/
t_expand	*init_node_no_quote(t_expand *node, t_expand *new_node);
t_expand	*expand_with_space(t_expand *node, t_expand *new_node, \
char **split, char *prev_q);
t_expand	*expand_linked_no_quote(t_expand *node, \
t_expand *new_node, char *prev_q);

/*-----expand_quote.c-----*/
t_expand	*init_node_quote(t_expand *node, t_expand *new_node, \
t_global_info *g_info);
t_expand	*expand_double_quote(t_expand *node, t_expand *new_node, \
t_global_info *g_info, char *prev);
t_expand	*expand_single_quote(t_expand *node, \
t_expand *new_node, char *prev);
t_expand	*expand_linked_quote(t_expand *node, t_expand *new_node, \
t_global_info *g_info, char *prev);

/*-----expand_tools.c-----*/
char		**convert_linked_array(t_expand *head);
char		**ft_strjoin2d(char **s1, char **s2);
int			search_in_env(t_env *env, char *string);
char		*to_lower(char *command);

/*-----expand_var.c-----*/
char		*join_expand_var(char *var, char *string, int index, \
t_global_info *g_info);
char		*extract_var(char *expand_split, char *expand_string, \
t_global_info *g_info);
char		*expand_var(char *string, t_global_info *g_info);

/*-----expander.c-----*/
t_expand	*quote_expand(t_expand *head, char *string, char c, int *i);
t_expand	*ft_expand(char *string);
char		**join_all_param(t_expand *head, char *param, \
t_global_info *g_info);
char		**expand_all_param(t_command *cmd);

#endif