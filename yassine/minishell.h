/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:09 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/17 10:28:53 by yajallal         ###   ########.fr       */
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


int search_in_env(t_env *env, char *string);




int  syntx_error_b(char **splt, t_global_info *g_info);
int check_empty(char *str);
int syntx_error_a(char **splt, t_global_info *g_info);
char *rem_quots(char *splt);
char	*ft_strjoin_char(char const *s1, char s2);


#endif