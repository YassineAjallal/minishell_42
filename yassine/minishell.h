/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:09 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/16 18:50:22 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./cmd_executer/cmd_executer.h"
#include "./built_in_command/built_in_command.h"
#include "structs.h"

char **lexer(char *str, t_global_info *g_info);
t_command  **rmplr_double_str(t_command **cmd,t_global_info g_info,int size);
t_command **rmplir_strct(char **splt, t_global_info *g_info);

// char *ft_expand(char *string, t_global_info *g_info);
// char **expand_all_param(t_command *cmd, t_global_info *g_info);
int search_in_env(t_env *env, char *string);

// void syntax_error(char *input);

// char	*ft_strjoin_char(char const *s1, char s2);
// char	*ft_substr_ya(char const *s, unsigned int start, size_t len);
// char *find_valr(char *expn,t_global_info g_ifo);
// char *remove_quots(char *splt,t_global_info g_info);
// char **expand_splt(char **splt,t_global_info g_info);

int  syntx_error_b(char **splt, t_global_info *g_info);
int check_empty(char *str);
int syntx_error_a(char **splt, t_global_info *g_info);
char *rem_quots(char *splt);
char	*ft_strjoin_char(char const *s1, char s2);
#endif