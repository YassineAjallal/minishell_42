/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:27:57 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/26 16:43:04 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_parsing *parsing;

	parsing = malloc(sizeof(t_parsing));
	parsing->number_of_pipe = 0;
	parsing->nb_single_redirect = 0;
	parsing->nb_double_redirect = 0;
	return 0;
}
