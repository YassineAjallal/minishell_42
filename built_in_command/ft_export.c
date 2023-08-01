/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:45:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 14:29:19 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

void	export_no_param(t_command *cmd)
{
	int	i;

	i = 0;
	sort_env_variables(cmd->g_info->export_env);
	while (i < cmd->g_info->export_env->nb_variables)
	{
		if (!cmd->g_info->export_env->variables[i].value)
			printf("declare -x %s\n", \
			cmd->g_info->export_env->variables[i].name);
		else if (ft_strlen(cmd->g_info->export_env->variables[i].value) > 0)
		{
			printf("declare -x %s=\"", \
			cmd->g_info->export_env->variables[i].name);
			print_export_value(cmd->g_info->export_env->variables[i].value);
			printf("\"\n");
		}
		else if (ft_strlen(cmd->g_info->export_env->variables[i].value) == 0)
			printf("declare -x %s=\"\"\n", \
			cmd->g_info->export_env->variables[i].name);
		i++;
	}
	cmd->g_info->exit_code = 0;
}

void	fill_list(t_env *env, t_variable *new_vars)
{
	int	i;

	i = 0;
	while (i < env->nb_variables)
	{
		new_vars[i].name = env_strdup(env->variables[i].name);
		free(env->variables[i].name);
		if (!env->variables[i].value)
			new_vars[i].value = NULL;
		else if (ft_strlen(env->variables[i].value) == 0)
		{
			new_vars[i].value = env_strdup("");
			free(env->variables[i].value);
		}	
		else
		{	
			new_vars[i].value = env_strdup(env->variables[i].value);
			free(env->variables[i].value);
		}
		i++;
	}
}

int	fill_var_list(t_variable new_var, t_env *env)
{
	t_variable	*new_vars;
	int			i;

	i = env->nb_variables;
	new_vars = malloc(sizeof(t_variable) * (env->nb_variables + 1));
	if (!new_vars)
		return (0);
	fill_list(env, new_vars);
	new_vars[i].name = env_strdup(new_var.name);
	if (!new_var.value)
		new_vars[i].value = NULL;
	else
		new_vars[i].value = env_strdup(new_var.value);
	env->nb_variables++;
	free(env->variables);
	env->variables = new_vars;
	return (1);
}

int	replace_variable(t_variable new_var, t_env *env)
{
	int	existed;

	existed = already_exist(new_var.name, env);
	if (existed > -1)
	{
		free(env->variables[existed].value);
		if (!new_var.value)
			env->variables[existed].value = NULL;
		else if (ft_strlen(new_var.value) == 0)
			env->variables[existed].value = env_strdup("");
		else
			env->variables[existed].value = env_strdup(new_var.value);
		return (1);
	}
	return (0);
}

int	export_normal_var(t_variable new_var, t_global_info *g_info)
{
	char	*tmp;

	tmp = env_strtrim(new_var.value, "\"\'");
	free(new_var.value);
	new_var.value = env_strdup(tmp);
	free(tmp);
	if (replace_variable(new_var, g_info->environ) && \
	replace_variable(new_var, g_info->export_env))
		return (1);
	if (!fill_var_list(new_var, g_info->environ))
	{
		return (0);
	}
	if (g_info->env_array)
		ft_free2d(g_info->env_array);
	g_info->env_array = convert_env_array(g_info->environ);
	if (!fill_var_list(new_var, g_info->export_env))
	{
		return (0);
	}
	return (1);
}
