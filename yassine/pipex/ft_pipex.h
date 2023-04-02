/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:57:54 by yajallal          #+#    #+#             */
/*   Updated: 2023/01/13 14:24:45 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>
# include "./libft/libft.h"

// ft_printerror.c
void	ft_perror(int fd, char *s, ...);
void	ft_errors(char *error, int ex);

// ft_cmd.c
char	*ft_cmdpath(char *cmd, char **envp);
char	**ft_envp(char **envp);
char	**ft_quotes(char *cmd);
char	*ft_cmd(char **paths, char *cmd);

// ft_free.c
void	ft_free(char *s1, char *s2);
void	ft_free2d(char **str, char *s);

// ft_files.c
void	ft_checkf(char *file, char *msg, int ex);
void	ft_checkr(char *file, int ex);
void	ft_checkw(char *file, int ex);
void	ft_checkx(char *file, int ex);

// ft_family.c
void	ft_parent(int output, int *fd_pipe, char **av, char **envp);
void	ft_child(int input, int *fd_pipe, char **av, char **envp);

// ft_process.c
void	ft_fork(int *fd_pipe, char **av, char **envp);
void	ft_redirect(int f1, int f2, int f3);

#endif
