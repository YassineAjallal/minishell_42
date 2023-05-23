/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:56:03 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 19:11:31 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

void	swap_variable(t_variable *var1, t_variable *var2)
{
	t_variable	*tmp;

	tmp = malloc(sizeof(t_variable));
	tmp->name = var1->name;
	tmp->value = var1->value;
	var1->name = var2->name;
	var1->value = var2->value;
	var2->name = tmp->name;
	var2->value = tmp->value;
	free(tmp);
}

void	sort_env_variables(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (i < env->nb_variables)
	{
		j = i + 1;
		while (j < env->nb_variables)
		{
			if (ft_strcmp(env->variables[i].name, env->variables[j].name) > 0)
				swap_variable(&env->variables[i], &env->variables[j]);
			j++;
		}
		i++;
	}
}

void	print_export_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (ft_strchr("\"$", value[i]))
			printf("\\");
		printf("%c", value[i]);
		i++;
	}
}
