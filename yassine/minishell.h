/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:09 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/31 01:27:49 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
// #include "./pipex/ft_pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_parsing
{
	char **split_using_pipe;
	char **split_unsing_redirect;
	int number_of_pipe;
	int nb_single_redirect;
	int nb_double_redirect;
} t_parsing;

// typedef struct s_pipe
// {
// 	int pipe[2];
// 	int
// } t_pipe;

#endif