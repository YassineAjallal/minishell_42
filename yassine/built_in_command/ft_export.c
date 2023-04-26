/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:45:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/26 15:35:57 by yajallal         ###   ########.fr       */
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
	char *tmp;
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
			printf("declare -x %s=\"%s\"\n", export->variables[i].name, export->variables[i].value);
		else if (ft_strlen(export->variables[i].value) == 0)
			printf("declare -x %s=""\n", export->variables[i].name);
		i++;
	}
}

/* fill a variables list */
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

/* add a new valid variable */
int export_normal_var(t_variable new_var, t_env *env, t_env *export)
{
	if (!fill_var_list(new_var, env))
		return (0);
	if (!fill_var_list(new_var, export))
		return (0);
	return (1);
}
