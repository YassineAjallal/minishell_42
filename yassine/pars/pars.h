/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 23:18:17 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
#define PARS_H

#include "../minishell.h"
#include "../structs.h"
int	syntx_error_a(char **splt, t_global_info *g_info);
int	syntx_error_b(char **splt, t_global_info *g_info);
int	error_redirect(char **splt);
t_file	**ft_strjoin_out(t_file **s1, char *s2, char *mode);
t_file	**ft_strjoin_in(t_file **s1, char *s2, char *mode);
char	**ft_strjoin_2d(char **s1, char *s2);
int	ft_strlen_out(t_file **str);
char	**lexer(char *str, t_global_info *g_info);
int	retu_if2(t_v *v, t_command **cmd);
int	retu_if1(t_v *v, t_command **cmd);
t_file	**ft_strdup_file(t_file **s1);
t_command	**rmplr_double_str(t_command **cmd, t_global_info g_info, int size);
void	initlize_dup_cmd(t_command **cmd, t_global_info *g_info);
void	check_rederect(t_command **cmd);
void	rmplr_parametr(t_command **cmd, char **splt);
void	rmplr_cmd(t_command **cmd);
int	chk_cmd_is_first_or_aftrederect(t_command **cmd, t_v *v);
void	dlt_herdoc_file(t_command **cmd);
void	quote(char *str, t_v *v, char *line);
int	quote1(char *str, t_v *v, char *line);

#endif