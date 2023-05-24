#include "../yassine/minishell.h"
#include "mini.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// enum s_cases 
// {
// 	quotes,
// 	redirects,
// };

typedef struct s_v
{
	int i;
	int j;
	char qts;
	int k;
}		t_v;

// typedef struct s_prompt
// {
// 	t_mini	*cmds;
// 	char	**envp;
// }		t_prompt;

// int is_skiped(char s)
// {
// 	if ((s != ' ' || s == '"' || s == '\'') && s != '\0')
// 	{
// 		return 1;
// 	}
// 	return 0;
// }
// while (1) {
// 				quote = 1;
// 				line[j++] = str[i++];
// 				while (str[i] != '"' && str[i] != '\0') {
// 					line[j++] = str[i++];
// 					if(str[i] == '\'')	
// 						quote = 2;
// 				}
// 				line[j++] = str[i++];
// 				if(str[i] == ' ' || str[i] == '\0' || str[i] == '>' || str[i] == '<')
// 				{
// 					printf("STOP | %c|\n",str[i]);
// 					break;
// 				}
// 				printf("-- %c --\n",str[i + 1]);
// 				sleep(1);
// 			}
char **lexer(char *str, t_global_info *g_info)
{
    int i = 0;
	char *line;
	int j = 0;
	int k = 0;
	int quote;
	line = malloc(sizeof(char ) * (ft_strlen(str) * 2));
	char **splt;
	while (str[i]) {
		quote = 0;
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
		else if(str[i] == '"' || str[i] == '\'')
		{
			quote =0;
			while (1) {
				if(str[i] == '"')
					quote = 1;
				else if(str[i] == '\'')
					quote = 2;
				else
				 	quote =-1;
				line[j++] = str[i++];
				while ((quote == 1 || quote == 2) && str[i] != '\0') {
					// printf("%c\t",str[i]);
					if(str[i] == '"' && quote == 1)
					{
						quote = -1;
						break;
					}
					if(str[i] == '\'' && quote == 2)
					{
						quote = -1;
						break;
					}
					line[j++] = str[i++];
				}
				line[j++] = str[i++];
				if(str[i - 1] == '\0' || str[i] == '\0'  ||str[i] == ' ' || str[i] == '>')
					break;
				// printf("|%c|\t",str[i]);
			}
			// printf("%d\n",quote);
			if(quote != -1)
			{
				perror("QUOTE");
				free(line);
				return NULL;
			}
			line[j++] = '\n';
		}
		else {
			line[j++] = str[i++];
		}
	}
	line[j] = 0;
	splt = ft_split(line, '\n');
	free(line);
	line = NULL;
	return splt;
}

// void parser(char **splt,char **env)
// {
// 	int i = 0;
// 	int expr_ok;
// 	int j = 0;
// 	int k = 0;
// 	int l = 0;
// 	int m = 0;
// 	int cma ;
// 	int p = 0;
// 	char *find;
// 	char *str;
// 	while (splt[i] != NULL) {
// 		j = 0;
// 		cma = 1;
// 		if(splt[i][0] == '\'')
// 			cma = 0;
// 		while (splt[i][j]) {
// 			k = j;
// 			expr_ok = 1;
// 			if(cma != 0)
// 			{
// 				if(splt[i][j] == '$')
// 				{
// 					str = NULL;
// 					find = NULL;
// 					k++;
// 					while (ft_isalpha(splt[i][k]) && splt[i][k] != '\0') {
// 						k++;
// 					}
// 					k--;
// 					str = ft_substr(splt[i],j + 1,k - 1);
// 					str = ft_strjoin(str, "=");
// 					l = 0;
// 					while (env[l]) {
// 						if((find = ft_strnstr(env[l], str,ft_strlen(env[l]))))
// 						{
// 							expr_ok =0;
// 							p = 0;
// 							while (find[p] != '=') {
// 								p++;
// 							}
// 							p++;
// 							find = ft_substr(find, p, ft_strlen(find));
// 						}
// 					l++;

// 					}
// 				}
// 			}
// 			j = k;
// 			if(expr_ok == 1)
// 				printf("%c",splt[i][j]);
// 			j++;
// 		}
// 		i++;
// 		printf("\n");
// 	}
// }
t_command  **rmplr_double_str(t_command **cmd,t_global_info g_info,int size)
{
	int j = 0;
	int i = 0;
	t_command **cmd_rtr;
	cmd_rtr = malloc((size) * sizeof(t_command *));
	i = 0;
	while (i < size)
	{
		cmd_rtr[i] = malloc(sizeof(t_command));

		i++;
	}
	i = 0;
	while (cmd[i]->ther) {
		cmd_rtr[i]->g_info = cmd[i]->g_info;
		cmd_rtr[i]->ther = cmd[i]->ther;
		cmd_rtr[i]->cmd = ft_strdup(cmd[i]->cmd);
		cmd_rtr[i]->redirect_in = cmd[i]->redirect_in;
		cmd_rtr[i]->redirect_out = cmd[i]->redirect_out;
		cmd_rtr[i]->herdoc = cmd[i]->herdoc;
		cmd_rtr[i]->infile = cmd[i]->infile;
		cmd_rtr[i]->outfile = cmd[i]->outfile;
		
		// cmd_rtr[i]->delemiter = cmd[i]->delemiter;
		cmd_rtr[i]->herdoc_stdout = cmd[i]->herdoc_stdout;
		i++;
	}
	cmd_rtr[i]->ther = 0;
	i = 0;
	j = 0;
	int cnt = 0;
	while (cmd[i]->ther) {
		j = 0;
		cnt = 0;
		while (cmd[i]->cmd_parameter[j] != NULL) {
			if(cmd[i]->cmd_parameter[j][0] != '\0')
				cnt++;
			j++;
		}
		cmd_rtr[i]->cmd_parameter = malloc((cnt + 1) * sizeof(char *));
		j = 0;
		cnt = 0;
		while (cmd[i]->cmd_parameter[j] != NULL) {
			if(cmd[i]->cmd_parameter[j][0] != '\0')
				cmd_rtr[i]->cmd_parameter[cnt++] = ft_strdup(cmd[i]->cmd_parameter[j]);
			j++;
		}
		cmd_rtr[i]->cmd_parameter[cnt]= NULL;
		i++;
	}
	i = 0;
	j = 0;
	return cmd_rtr;
}




t_file **ft_strjoin_in(t_file **s1, char *s2,char *mode)
{
	int i;
	int j;
	t_file **new_array;
	
	i = 0;
	j = 0;
	new_array = malloc(sizeof(t_file *) * (ft_strlen_out(s1) + 2));
	if (!new_array)
		return (NULL);
	while(s1[i] && s1)
	{
		new_array[i] = malloc(1 * sizeof(t_file));
		new_array[i]->file = s1[i]->file;
		new_array[i]->mode = s1[i]->mode;
		i++;
	}
	new_array[i] = malloc(1 * sizeof(t_file));
	new_array[i]->file = s2;
	if((mode[0] == '<' && mode[1] == '<'))
		new_array[i]->mode = false;
	else if (mode[0] == '<' )
		new_array[i]->mode = true;
	i++;
	new_array[i] = NULL;
	return (new_array);
}
void free_outfile(t_file **outfile) {
	int i = 0;
	int j = 0;
    if (outfile && *outfile) {
        while(outfile[i])
		{
			free(outfile[i++]);
		}
		free(outfile);
    }
}
// void free_outfile(t_file **outfile) {
//     if (outfile && *outfile) {
//         free(*outfile);
//         *outfile = NULL;
//     }
// }
t_command **rmplir_strct(char **splt, t_global_info *g_info)
{
	t_command **cmd;
	char *ss ;
	int size = 0;
	char *str;
	int stop = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int cnt = 0;
	int whr = 0;
	// bax nhseb xhal mn '|' kayna
	while (splt[i] != NULL) {
		if(splt[i][j] == '|')
			cnt++;
		i++;
	}
	cmd = malloc((cnt + 2) * sizeof(t_command *));
	size = cnt + 2;
	g_info->nb_pipe = cnt;
	i = 0;
	while (i < cnt + 2)
	{
		cmd[i] = malloc(sizeof(t_command));
		i++;
	}
	// hene 3amert cmd.cmd bi axmen command kayna fkola pipe
	i = 0;
	k = 0;
	j = 0;
	int strt = 0;
	while (splt[i] != NULL) {
		if(strt == 0)
		{
			cmd[whr]->ther = 1;
			strt = 1;
			whr++;
		}
		if (splt[i][0] == '|') {
			strt = 0;
		}
		i++;
	}
	cmd[whr]->ther = 0;
	//hena ghir 3mart kola pipe bi 0 fi > < >>
	i = 0;
	while (cmd[i]->ther != 0) {
		cmd[i]->redirect_in = 0;
		cmd[i]->redirect_out = 0;
		cmd[i]->herdoc = 0;
		cmd[i]->infile = NULL;
		cmd[i]->outfile = NULL;
		// cmd[i]->delemiter = NULL;
		cmd[i]->herdoc_stdout = 0;
		cmd[i]->g_info = g_info;
		i++;
	}

	i = 0;
	j = 0;
	whr = 0;
	stop = 0;
	// hene fi lowl hsebt xhal kayn mn argument fkola pipe
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
	// 
	i = 0;
	j = 0;
	while(cmd[i]->ther)
    {
        j = 0;
        while(cmd[i]->cmd_parameter[j] != NULL)
        {
            if(cmd[i]->cmd_parameter[0][0] == '>' || cmd[i]->cmd_parameter[0][0] == '<' || (cmd[i]->cmd_parameter[0][0] == '<' && cmd[i]->cmd_parameter[0][1] == '<') || (cmd[i]->cmd_parameter[0][0] == '>' && cmd[i]->cmd_parameter[0][1] == '>'))
			{
				while (cmd[i]->cmd_parameter[j + 2] != NULL && (cmd[i]->cmd_parameter[j][0] == '<' || cmd[i]->cmd_parameter[j][0] == '>')) {
					if (cmd[i]->cmd_parameter[j + 1] == NULL)
						break;
					j+=2;
				}
				cmd[i]->cmd = cmd[i]->cmd_parameter[j];
				break;
			}
			else {
				cmd[i]->cmd = cmd[i]->cmd_parameter[0];
				break;
			}
        }
		ss =rem_quots(cmd[i]->cmd);
		if(cmd[i]->cmd[0] == '<' || cmd[i]->cmd[0] == '>')
		{
			cmd[i]->cmd = NULL;
		}
		if(ss[0] == '\0')
		{
			cmd[i]->cmd = ft_strdup("");
		}
		free(ss);
        i++;
    }
	// hena ghadi nbda n9alb 3la wax kayn redirect o dakxi fi kola pipe

	i = 0;
	j = 0;
	// while (cmd[i]->ther) {
	// 	printf("%s\n",cmd[i]->cmd);
	// 	i++;
	// }
	cnt = 0;
	t_file **ll;
	while(cmd[i]->ther)
    {
        j = 0;
        while(cmd[i]->cmd_parameter[j] != NULL)
        {
			k = 0;
			if(cmd[i]->cmd_parameter[j][0] == '<')
			{
				if(cmd[i]->redirect_in == 0)
				{
					cmd[i]->redirect_in = 1;
					k = 0;
					cnt = 1;
					j += 1;
					cmd[i]->infile = malloc(2 * sizeof(t_file *));
					if(cmd[i]->cmd_parameter[j])
					{
						cmd[i]->infile[0] = malloc(1 * sizeof(t_file));
						cmd[i]->infile[1] = malloc(1 * sizeof(t_file));
						if(cmd[i]->cmd_parameter[j - 1][0] == '<' && cmd[i]->cmd_parameter[j - 1][1] == '<')
						{
							cmd[i]->herdoc = true;
							cmd[i]->infile[k]->mode = false;
						}
						else
							cmd[i]->infile[k]->mode = true;
						cmd[i]->infile[0]->file = cmd[i]->cmd_parameter[j];
						free(cmd[i]->infile[1]);
						cmd[i]->infile[1] = NULL;
						
					}
					if(cmd[i]->cmd_parameter[j] == NULL){
						break;
					}
				}
				else {
					if(cmd[i]->cmd_parameter[j + 1])
					{
						
						ll = ft_strjoin_out(cmd[i]->infile, cmd[i]->cmd_parameter[j],cmd[i]->cmd_parameter[j - 1]);
						free_outfile(cmd[i]->infile);
						cmd[i]->infile = ll;
					}
					if(cmd[i]->cmd_parameter[j] == NULL){
						break;
					}
				}
			}
            else if(cmd[i]->cmd_parameter[j][0] == '>')
			{
				if(cmd[i]->redirect_out == 0)
				{
					cmd[i]->redirect_out = 1;
					k = 0;
					cnt = 1;
					j += 1;
					cmd[i]->outfile = malloc(2 * sizeof(t_file *));
					if(cmd[i]->cmd_parameter[j])
					{
						cmd[i]->outfile[0] = malloc(1 * sizeof(t_file));
						cmd[i]->outfile[1] = malloc(1 * sizeof(t_file));
						if(cmd[i]->cmd_parameter[j - 1][0] == '>' && cmd[i]->cmd_parameter[j - 1][1] == '>')
							cmd[i]->outfile[k]->mode = false;
						else
							cmd[i]->outfile[k]->mode = true;
						cmd[i]->outfile[0]->file = cmd[i]->cmd_parameter[j];
						free(cmd[i]->outfile[1]);
						cmd[i]->outfile[1] = NULL;
						
					}
					if(cmd[i]->cmd_parameter[j] == NULL){
						break;
					}
				}
				else {
					if(cmd[i]->cmd_parameter[j + 1])
					{
						
						j++;

						ll = ft_strjoin_out(cmd[i]->outfile, cmd[i]->cmd_parameter[j],cmd[i]->cmd_parameter[j - 1]);
						free_outfile(cmd[i]->outfile);
						cmd[i]->outfile = ll;
					}
					if(cmd[i]->cmd_parameter[j] == NULL){
						break;
					}
				}
			}
			j++;
        }
        i++;
    }
	k = 0;
	i = 0;
	j = 0;
	// display each pipe rederction;'
	// while (cmd[i]->ther) {
	// 	printf("----herdoc LIST-----\n");
	// 	j = 0;
	// 	if(cmd[i]->delemiter == NULL)
	// 		printf("****  NO OUT  >> *****\n");
	// 	else
	// 	 	while (cmd[i]->delemiter[j] != NULL) {
	// 			printf("%s\n",cmd[i]->delemiter[j++]);
	// 		}
	// 	i++;
	// }
	// i = 0;
	// j = 0;
	// while (cmd[i]->ther) {
	// 	printf("----IN_FILE LIST-----\n");
	// 	j = 0;
	// 	if(cmd[i]->infile == NULL)
	// 		printf("****  NO IN  >> *****\n");
	// 	else
	// 	 	while (cmd[i]->infile[j] != NULL) {
	// 			printf("%s\n",cmd[i]->infile[j++]);
	// 		}
	// 	i++;
	// }
	// i = 0;
	// j = 0;
	// while (cmd[i]->ther) {
	// 	printf("----IN_FILE LIST-----\n");
	// 	j = 0;
	// 	if(cmd[i]->outfile == NULL)
	// 		printf("****  NO IN  >> *****\n");
	// 	else
	// 	 	while (cmd[i]->outfile[j] != NULL) {
	// 			if (cmd[i]->outfile[j]->mode == true) {
	// 				printf("mode :TRUE  >\t|");
	// 			}
	// 			else {
	// 				printf("mode :FALSE  >>\t|");
	// 			}
	// 			printf("%s\n",cmd[i]->outfile[j++]->file);
	// 		}
	// 	i++;
	// }
	t_command ** cmd_rtr;
	i = 0;
	j = 0;
	while (cmd[i]->ther) {
		j = 0;
		while (cmd[i]->cmd_parameter[j] != NULL) {
			if(((cmd[i]->cmd_parameter[j][0] == '>' && cmd[i]->cmd_parameter[j][1] == '>') || (cmd[i]->cmd_parameter[j][0] == '<' && cmd[i]->cmd_parameter[j][1] == '<')) && cmd[i]->cmd_parameter[j + 1] != NULL )
			{
				// printf("**  in  **\n");
				cmd[i]->cmd_parameter[j] = "";
				cmd[i]->cmd_parameter[j + 1] = "";
				j++;
			}
			if((cmd[i]->cmd_parameter[j][0] == '>' || cmd[i]->cmd_parameter[j][0] == '<') && cmd[i]->cmd_parameter[j + 1] != NULL)
			{
				// printf("|   IN  |\n");
				cmd[i]->cmd_parameter[j] = "";
				cmd[i]->cmd_parameter[j + 1] = "";
				j++;
			}
			j++;
		}
		// printf("------------\n");
		i++;
	}
	i = 0;
	j = 0;
	cmd_rtr = rmplr_double_str(cmd,*g_info, size);
	i = 0;
	while(cmd[i]->ther)
	{
		free(cmd[i]->cmd_parameter);
		// if(cmd[i]->outfile)
		// {
		// 	j = 0;
		// 	while(cmd[i]->outfile[j]!= NULL)
		// 	{
		// 		free(cmd[i]->outfile[j++]);
		// 	}
		// 	printf("%d\n\n-------------\n",j);
		// 	free(cmd[i]->outfile);
		// }
		// if(cmd[i]->infile)
		// {
		// 	j = 0;
		// 	while(cmd[i]->infile[j]!= NULL)
		// 	{
		// 		free(cmd[i]->infile[j++]);
		// 	}
		// 	// free(cmd[i]->outfile[0]);
		// 	printf("%d\n\n-------------\n",j);
		// 	// free(cmd[i]->outfile[j]);
		// 	free(cmd[i]->infile);
		// }
		free(cmd[i]);
		i++;
	}
	free(cmd[i]);
	free(cmd);
	// free_first(cmd);
	return  cmd_rtr;
}

void free_first(t_command **cmd)
{
	int i = 0;
	int j = 0;
	while(cmd[i]->ther)
	{
		free(cmd[i]->cmd_parameter);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
int error_redirect(char **splt)
{
	int i = 0;
	int j = 0;
	while (splt[i] != NULL) {
		// printf("{{%s}}\n",splt[i]);
		if(splt[i][0] == '<' || splt[i][0] == '>')
		{
			// printf("$$  %s  $$\n",splt[i + 1]);
			if(splt[i + 1] == NULL)
				return 0;
			if(splt[i + 1][0] == '<' || splt[i + 1][0] == '>')
				return 0;
		}
		i++;
	}
	return 1;
}
t_global_info g_info;

void free_split(char **splt)
{
	int i = 0;
	while (splt[i])
	{
		free(splt[i++]);
	}
	free(splt);
}
void free_last(t_command **cmd)
{
	int i;
	i = 0;
	int j = 0;

	while(cmd[i]->ther)
	{
		j = 0;
		while(cmd[i]->cmd_parameter[j])
		{
			free(cmd[i]->cmd_parameter[j++]);
		}
		if(cmd[i]->outfile)
		{
			j = 0;
			while(cmd[i]->outfile[j]!= NULL)
			{
				free(cmd[i]->outfile[j++]);
			}
			free(cmd[i]->outfile);
		}
		if(cmd[i]->infile)
		{
			j = 0;
			while(cmd[i]->infile[j]!= NULL)
			{
				free(cmd[i]->infile[j++]);
			}
			free(cmd[i]->infile);
		}
		free(cmd[i]->cmd_parameter);
		free(cmd[i]->cmd);
		free(cmd[i++]);
	}
	free(cmd[i]);
	free(cmd);
}

void    handler(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void quit(int signum)
{
	rl_redisplay();
}
void handleCtrlBackslash(int sig)
{
	exit(0);
}
int main(int ac,char **av,char **env)
{
	char	*str;
	int		i;
	char **splt;
	t_command **cmd;
	i = 0;
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, quit);
		str = readline("Shell->");
		add_history(str);
		if(str != NULL)
		{
        	splt = lexer(str,&g_info);
			if(splt == NULL)
			{
				i = 0;
			}
			else 
			{
				if(syntx_error_a(splt,&g_info) && syntx_error_b(splt,&g_info))
				{
					
					cmd = rmplir_strct(splt, &g_info);
					free_last(cmd);
				}
				free_split(splt);
			}
			free(str);
		}
		else
			exit(0);
	}
}