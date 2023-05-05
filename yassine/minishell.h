/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:09 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/04 18:00:56 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./tools/tools.h"
#include "./built_in_command/built_in_command.h"
#include "structs.h"

char **lexer(char *str,char **env);
t_command **rmplir_strct(char **splt, t_global_info *g_info);
#endif