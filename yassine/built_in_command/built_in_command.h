/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:43:56 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 18:30:40 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_COMMAND_H
# define BUILT_IN_COMMAND_H

# include "../structs.h"

/*-----env_export_tools.c-----*/
void	swap_variable(t_variable *var1, t_variable *var2);
void	sort_env_variables(t_env *env);
void	print_export_value(char *value);

/*-----export_param.c-----*/
int		already_exist(char *name, t_env *env);
int		valid_name(char *name);
int		var_more_eq(char *eq_split, char *param, t_global_info *g_info);
int		ft_export(t_command *cmd);

/*-----ft_cd.c-----*/
int		cd_no_param(t_command *cmd);
int		cd_with_param(t_command *cmd);
int		ft_cd(t_command *cmd);

/*-----ft_echo.c-----*/
int		just_n(char *str);
void	ft_echo(t_command *cmd);

/*-----ft_env.c-----*/
int		get_until_equal(char *str);
t_env	*dup_env(char **inherit_env);
char	**convert_env_array(t_env *env);
void	ft_env(t_command *cmd);

/*-----ft_exit.c-----*/
void	ft_perror(int fd, char *s, char *str);
int		exit_one_pram(t_command *cmd);
int		exit_more_param(t_command *cmd);
int		ft_exit(t_command *cmd);

/*-----ft_export.c-----*/
void	export_no_param(t_command *cmd);
void	fill_list(t_env *env, t_variable *new_vars);
int		fill_var_list(t_variable new_var, t_env *env);
int		replace_variable(t_variable new_var, t_env *env);
int		export_normal_var(t_variable new_var, t_global_info *g_info);

/*-----ft_pwd.c-----*/
void	ft_pwd(t_command *cmd);

/*-----ft_unset.c-----*/
int		search_env(t_env *env, char *to_search, int *var_pos);
void	delete_var(t_env *env, int var_pos);
int		unset_one_var(char *unset_var, t_env *env);
int		ft_unset(t_command *cmd);

/*-----tools.c-----*/
int		ft_strlen2d(char **str);
char	*multiple_join(char **path, int length);
void	ft_free2d(char **str);

/*-----tools1.c-----*/
char	*env_substr(char *s, unsigned int start, size_t len);
void	*env_calloc(size_t count, size_t size);
char	*env_strdup(const char *s1);
char	*env_strjoin(char const *s1, char const *s2);
#endif