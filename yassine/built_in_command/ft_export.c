/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:45:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/12 11:49:37 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

/* swap to environment variables */
void swap_variable(t_variable *var1, t_variable *var2)
{
	t_variable *tmp;
	
	tmp = malloc(sizeof(t_variable));
	tmp->name = var1->name;
	tmp->value = var1->value;

	var1->name = var2->name;
	var1->value = var2->value;

	var2->name = tmp->name;
	var2->value = tmp->value;
	free(tmp);
}

/* sort environment variables */
void sort_env_variables(t_env *env)
{
	int i;
	int j;
	size_t length;

	i = 0;
	while(i < env->nb_variables)
	{
		j = i + 1;
		while (j < env->nb_variables)
		{
			if (ft_strlen(env->variables[i].name) > ft_strlen(env->variables[j].name))
				length = ft_strlen(env->variables[i].name);
			else
				length = ft_strlen(env->variables[j].name);
			if (ft_strncmp(env->variables[i].name, env->variables[j].name, length) > 0)
				swap_variable(&env->variables[i], &env->variables[j]);
			j++;
		}
		i++;
	}
}

/* export with no parameter */
void print_export_value(char *value)
{
	int i;

	i = 0;
	while(value[i])
	{
		if (ft_strchr("\"$", value[i]))
			printf("\\");
		printf("%c", value[i]);
		i++;
	}
}
void export_no_param(t_env *export)
{
	int i;

	i = 0;
	sort_env_variables(export);
	while(i < export->nb_variables)
	{
		if (!export->variables[i].value)
			printf("declare -x %s\n", export->variables[i].name);
		else if (ft_strlen(export->variables[i].value) > 0)
		{
			printf("declare -x %s=\"", export->variables[i].name);
			print_export_value(export->variables[i].value);
			printf("\"\n");
		}
		else if (ft_strlen(export->variables[i].value) == 0)
			printf("declare -x %s=\"\"\n", export->variables[i].name);
		i++;
	}
}

/* add new variable */
int fill_var_list(t_variable new_var, t_env *env)
{
	t_variable *new_vars;
	int i;

	i = 0;
	new_vars = malloc(sizeof(t_variable) * (env->nb_variables + 1));
	if (!new_vars)
		return (0);
	while (i < env->nb_variables)
	{
		new_vars[i].name = ft_strdup(env->variables[i].name);
		free(env->variables[i].name);
		if (!env->variables[i].value)
			new_vars[i].value = NULL;
		else if (ft_strlen(env->variables[i].value) == 0)
		{
			new_vars[i].value = ft_strdup("");
			free(env->variables[i].value);
		}	
		else
		{	
			new_vars[i].value = ft_strdup(env->variables[i].value);
			free(env->variables[i].value);
		}
		i++;
	}
	new_vars[i].name = ft_strdup(new_var.name);
	if (!new_var.value)
		new_vars[i].value = NULL;
	else
		new_vars[i].value = ft_strdup(new_var.value);
	env->nb_variables++;
	free(env->variables);
	env->variables = new_vars;
	return (1);
}
/* reblace the old var by the new var if it is already exist*/
int replace_variable(t_variable new_var, t_env *env)
{
	int existed;
	existed = already_exist(new_var.name, env);
	if (existed > -1)
	{
		free(env->variables[existed].value);
		if (!new_var.value)
			env->variables[existed].value = NULL;
		else if (ft_strlen(new_var.value) == 0)
			env->variables[existed].value = ft_strdup("");
		else
			env->variables[existed].value = ft_strdup(new_var.value);
		return (1);
	}
	return (0);
}
/* add a new vriable to export and env */
int export_normal_var(t_variable new_var, t_global_info *g_info)
{
	char *tmp;

	tmp = ft_strtrim(new_var.value, "\"\'");
	free(new_var.value);
	new_var.value = tmp;
	if (replace_variable(new_var, g_info->environ) && replace_variable(new_var, g_info->export_env))
		return (1);
	if (!fill_var_list(new_var, g_info->environ))
		return (0);
	if (g_info->env_array)
		ft_free2d(g_info->env_array);
	g_info->env_array = convert_env_array(g_info->environ);
	if (!fill_var_list(new_var, g_info->export_env))
		return (0);
	return (1);
}
