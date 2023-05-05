/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hamza.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:53:45 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/05 11:22:01 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
char **lexer(char *str,char **env)
{
    int i = 0;
	char *line;
	int j = 0;
	int k = 0;
	int quote = 0;
	line = malloc(sizeof(char ) * (ft_strlen(str) * 2));
	char **splt;
	while (str[i]) {
		if(str[i] == ' ')
		{
			line[j++] = '\n';
			i++;
		}
		else if(str[i] == '|')
		{
			line[j++] = '\n';
			line[j++] = str[i++];
			line[j++] = '\n';
		}
		else if(str[i] == '<' && str[i + 1] == '<')
		{
			line[j++] = '\n';
			line[j++] = str[i];
			line[j++] = str[i + 1];
			line[j++] = '\n';
			i +=2;
		}
		else if(str[i] == '>' && str[i + 1] == '>')
		{
			line[j++] = '\n';
			line[j++] = str[i];
			line[j++] = str[i + 1];
			line[j++] = '\n';
			i +=2;
		}
		else if(str[i] == '>')
		{
			line[j++] = '\n';
			line[j++] = str[i++];
			line[j++] = '\n';
		}
		else if(str[i] == '<')
		{
			line[j++] = '\n';
			line[j++] = str[i++];
			line[j++] = '\n';
		}
		else if(str[i] == '"')
		{
			quote = 1;
			line[j++] = str[i++];
			while (str[i] != '"') {
				line[j++] = str[i++];
			}
			line[j++] = str[i++];
			line[j++] = '\n';
		}
		else if(str[i] == '\'')
		{
			quote = 1;
			line[j++] = str[i++];
			while (str[i] != '\'') {
				line[j++] = str[i++];
			}
			line[j++] = str[i++];
			line[j++] = '\n';
		}
		else {
			line[j++] = str[i++];
		}
	}
	line[j] = 0;
	splt = ft_split(line, '\n');
	return splt;
}

t_command **rmplir_strct(char **splt, t_global_info *g_info)
{
	t_command **cmd;
	char *str;
	int stop = 0;
	char **full_cmd;
	int i = 0;
	int j = 0;
	int k = 0;
	int cnt = 0;
	int whr = 0;
	while (splt[i] != NULL) {
		if(splt[i][j] == '|')
			cnt++;
		i++;
	}
	cmd = malloc((cnt + 2) * sizeof(t_command *));
	g_info->nb_pipe = cnt;
	i = 0;
	while (i < cnt + 2)
	{
		cmd[i] = malloc(sizeof(t_command));
		cmd[i]->g_info = g_info;
		i++;
	}
	i = 0;
	k = 0;
	j = 0;
	int strt = 0;
	while (splt[i] != NULL) {
		if(strt == 0)
		{
			cmd[whr]->ther = 1;
			cmd[whr]->cmd = splt[i];
			strt = 1;
			whr++;
		}
		if (splt[i][0] == '|') {
			strt = 0;
		}
		i++;
	}
	cmd[whr]->ther = 0;
	i = 0;
	while (cmd[i]->ther != 0) {
		cmd[i]->redirect_in = 0;
		cmd[i]->redirect_out = 0;
		cmd[i]->redirect_append = 0;
		cmd[i]->herdoc = 0;
		cmd[i]->infile = NULL;
		cmd[i]->outfile = NULL;
		cmd[i]->delemiter = NULL;
		i++;
	}

	i = 0;
	j = 0;
	whr = 0;
	stop = 0;
	while (splt[i] != NULL) {
        k = i;
        cnt = 0;
        while (splt[k][0] != '|') 
        {
            cnt++;
            k++;
            if(splt[k] == NULL)
                break;
        }
        cmd[whr]->cmd_parameter = malloc(sizeof(char *) * (cnt + 1));
        i = k;
        if (splt[i] == NULL) 
            break;
        i++;
        whr++;
    }
	// hene bdit kan3amr fiha
    i = 0;
    j = 0;
    whr = 0;
    k = 0;
    while (splt[i]) {
        if(splt[i][0]  != '|')
        {
            cmd[k]->cmd_parameter[j++] = splt[i];
            // j++;
        }
        else{
            cmd[k]->cmd_parameter[j] = NULL;
            j = 0;
            k++;
        }
        i++;
        if(splt[i]  == NULL)
            cmd[k]->cmd_parameter[j] = NULL;
    }

	i = 0;
    j = 0;
	// hena printit mora ma3amrt struct bi argument dyla kola pipe
	// while(cmd[i]->ther)
    // {
    //     j = 0;
    //     while(cmd[i]->cmd_parameter[j] != NULL)
    //     {
    //         printf("%s\n",cmd[i]->cmd_parameter[j++]) ;
    //     }
    //     i++;
    // }

	i = 0;
	j = 0;
	return  cmd;
}