/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_function.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 02:16:39 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/02 02:18:52 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_FUNCTION_H
#define PIPE_FUNCTION_H

void	ft_checkf(char *file, char *msg, int ex);
void	ft_checkw(char *file, int ex);
void	ft_checkr(char *file, int ex);
void	ft_checkx(char *cmd, int ex);

void	exec_cmd(char **av, char **envp);

char	**ft_envp(char **envp);
char	*ft_cmd(char **paths, char *cmd);
char	*ft_cmdpath(char *cmd, char **envp);
char	**ft_quotes(char *cmd);
#endif