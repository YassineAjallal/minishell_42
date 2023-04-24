/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:45:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/24 15:14:30 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

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

void export_no_param(t_env *export)
{
	int i;

	i = 0;
	sort_env_variables(export);
	while(i < export->nb_variables)
	{
		if (export->variables[i].value)
			printf("declare -x %s=\"%s\"\n", export->variables[i].name, export->variables[i].value);
		else
			printf("declare -x %s\n", export->variables[i].name);
		i++;
	}
}


int main(int ac, char **av, char **env)
{
	t_env *environ;
	environ = dup_env(env);
	export_no_param(environ);
}
