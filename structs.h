/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:28:30 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/30 15:17:54 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./libft/libft.h"
# include "./ft_malloc/ft_malloc.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h> 
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_expand
{
	int				index;
	char			*value;
	struct s_expand	*next;
}	t_expand;

typedef struct s_v
{
	int		i;
	int		j;
	int		k;
	int		cnt;
	int		size;
	int		quote;
	int		whr;
	char	*str;
	char	s;
}			t_v;

typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

typedef struct s_env
{
	int				nb_variables;
	t_variable		*variables;
}	t_env;

typedef struct s_global_info
{
	t_env	*environ;
	t_env	*export_env;
	char	**env_array;
	int		exit_code;
	int		nb_pipe;
	int		old_stdout;
	int		old_stdin;
	int		status;
	int		signal;
	int		heredoc_exit;
}	t_global_info;

typedef struct s_file
{
	char	*file;
	bool	mode;
}	t_file;

typedef struct s_command
{
	int				ther;
	char			*cmd;
	char			*command_path;
	char			**cmd_parameter;
	bool			built_in;
	bool			redirect_in;
	bool			redirect_out;
	bool			herdoc;
	t_file			**infile;
	t_file			**outfile;
	int				herdoc_stdout;
	t_global_info	*g_info;
}	t_command;

/*-----ambiguous.c-----*/
int			ambiguous_checker(char *file, t_global_info *g_info);
char		*ambiguous_redirect(char *file, t_global_info *g_info);

/*-----free_infos.c-----*/
void		free_env(t_env *env);
void		free_infos(t_global_info *g_info);

/*-----linked_list-----*/
t_expand	*add_new_node(char *value, int index, t_expand *head);
t_expand	*delete_node(t_expand *head, int index);
void		num_list(t_expand *head);
int			lst_size(t_expand *head);
t_expand	*delete_empty(t_expand *head);

#endif