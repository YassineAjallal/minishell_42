/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:14:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/26 16:35:19 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int valid_name(char *name)
{
	int i;

	i = 0;
	if (!ft_isalpha(name[i]))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
			return (0);
		i++;
	}
	return (1);
}

int ft_export(char *user_input, t_global_info *g_info)
{
	char **vars;
	char **equal_split;
	int error_count;
	int equal_pos;
	t_variable new_var;

	int i;
	i = 0;
	error_count = 0;
	vars = ft_split(user_input, ' ');
	while (vars[i])
	{
		equal_split = ft_split(vars[i], '=');
		if (ft_strlen2d(equal_split) == 1)
		{
			if (valid_name(equal_split[0]))
			{
				new_var.name = ft_strdup(equal_split[0]);
				new_var.value = NULL;
				fill_var_list(new_var, g_info->export_env);
			}
			else
				error_count++;
		}
		else if (ft_strlen2d(equal_split) > 1)
		{
			if (valid_name(equal_split[0]))
			{		
				equal_pos = get_until_equal(vars[i]);
				new_var.name = ft_substr(vars[i], 0, equal_pos);
				new_var.value = ft_substr(vars[i], equal_pos + 1, ft_strlen(vars[i]));
				export_normal_var(new_var, g_info->environ, g_info->export_env);
			}
			else
				error_count++;
		}
		else
			error_count++;
		i++;
	}
	return (error_count);
}
int main(int ac, char **av, char **environ)
{
	t_global_info *g_info;
	
	g_info = malloc(sizeof(t_global_info));
	g_info->environ = dup_env(environ);
	g_info->export_env = dup_env(environ);
	ft_export(av[1], g_info);
	ft_env(g_info->environ);
	printf("\n-----------------------------------------------------\n\n");
	export_no_param(g_info->export_env);
	return 0;
}
