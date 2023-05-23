/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:28:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 18:16:59 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int	get_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

/* duplicate the origin environment */
t_env	*dup_env(char **inherit_env)
{
	t_env	*env;
	int		equal_pos;
	int		i;

	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->nb_variables = ft_strlen2d(inherit_env);
	env->variables = malloc(sizeof(t_variable) * (env->nb_variables));
	if (!env->variables)
		return (NULL);
	while (i < env->nb_variables)
	{
		equal_pos = get_until_equal(inherit_env[i]);
		env->variables[i].name = ft_substr(inherit_env[i], 0, equal_pos);
		env->variables[i].value = ft_substr(inherit_env[i], equal_pos + 1, \
		ft_strlen(inherit_env[i]));
		i++;
	}
	return (env);
}

/* convert environ to 2d array */
char	**convert_env_array(t_env *env)
{
	char	**env_array;
	char	*add_equal;
	int		i;

	i = 0;
	env_array = malloc(sizeof(char *) * (env->nb_variables + 1));
	if (!env_array)
		return (NULL);
	while (i < env->nb_variables)
	{
		add_equal = ft_strjoin(env->variables[i].name, "=");
		env_array[i] = ft_strjoin(add_equal, env->variables[i].value);
		free(add_equal);
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

/* print environment variables */
void	ft_env(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->g_info->environ->nb_variables)
	{
		printf("%s=%s\n", cmd->g_info->environ->variables[i].name, \
		cmd->g_info->environ->variables[i].value);
		i++;
	}
	cmd->g_info->exit_code = 0;
}
