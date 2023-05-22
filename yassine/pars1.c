#include "minishell.h"
#include <stdio.h>

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
// int ft_strlen2d(char **str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i])
// 		i++;
// 	return (i);
// }

char **ft_strjoin_2d(char **s1, char *s2)
{
	int i;
	int j;
	char **new_array;
	
	i = 0;
	j = 0;
	new_array = malloc(sizeof(char *) * (ft_strlen2d(s1) + 2));
	if (!new_array)
		return (NULL);
	while(s1[i] && s1)
	{
		new_array[i] = ft_strdup(s1[i]);
		i++;
	}
	new_array[i] = ft_strdup(s2);
	i++;
	new_array[i] = NULL;
	return (new_array);
}
int ft_strlen_out(t_file **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}
t_file **ft_strjoin_out(t_file **s1, char *s2,char *mode)
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
	if((mode[0] == '>' && mode[1] == '>'))
		new_array[i]->mode = false;
	else if (mode[0] == '>' )
		new_array[i]->mode = true;
	i++;
	new_array[i] = NULL;
	return (new_array);
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
				if(str[i] == ' ' || str[i] == '>' || str[i] == '\0' || str[i - 1] == '\0')
					break;
				// printf("|%c|\t",str[i]);
			}
			// printf("%d\n",quote);
			if(quote != -1)
			{
				ft_putstr_fd("minishell: unexpected EOF while looking for matching\n", 2);
				g_info->exit_code = 2;
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
	return splt;
}

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
		cmd_rtr[i]->cmd = cmd[i]->cmd;
		cmd_rtr[i]->redirect_in = cmd[i]->redirect_in;
		cmd_rtr[i]->redirect_out = cmd[i]->redirect_out;
		cmd_rtr[i]->herdoc = cmd[i]->herdoc;
		cmd_rtr[i]->infile = cmd[i]->infile;
		cmd_rtr[i]->outfile = cmd[i]->outfile;
		cmd_rtr[i]->delemiter = cmd[i]->delemiter;
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
				cmd_rtr[i]->cmd_parameter[cnt++] = cmd[i]->cmd_parameter[j];
			j++;
		}
		cmd_rtr[i]->cmd_parameter[cnt]= NULL;
		i++;
	}
	i = 0;
	j = 0;
	return cmd_rtr;
}

t_command **rmplir_strct(char **splt, t_global_info *g_info)
{
	t_command **cmd;
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
		cmd[i]->delemiter = NULL;
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
		char *ss =rem_quots(cmd[i]->cmd);
		if(cmd[i]->cmd[0] == '<' || cmd[i]->cmd[0] == '>')
		{
			cmd[i]->cmd = NULL;
		}
		if(ss[0] == '\0')
		{
			cmd[i]->cmd = ft_strdup("");
		}
		// printf("%s\n",cmd[i]->cmd);
        i++;
    }
	// hena ghadi nbda n9alb 3la wax kayn redirect o dakxi fi kola pipe

	i = 0;
	j = 0;
	// while (cmd[i]->ther) {
	// 	printf("%s\n",cmd[i]->cmd);
	// 	i++;
	// }
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
						cmd[i]->infile[1] = NULL;
						
					}
					if(cmd[i]->cmd_parameter[j] == NULL){
						break;
					}
				}
				else {
					if(cmd[i]->cmd_parameter[j + 1])
					{
						
						j++;
						cmd[i]->infile = ft_strjoin_in(cmd[i]->infile, cmd[i]->cmd_parameter[j],cmd[i]->cmd_parameter[j - 1]);
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
						cmd[i]->outfile = ft_strjoin_out(cmd[i]->outfile, cmd[i]->cmd_parameter[j],cmd[i]->cmd_parameter[j - 1]);
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
	// display each pipe rederction
	// while (cmd[i]->ther) {
	// 	printf("----OUT_FILE LIST-----\n");
	// 	if(cmd[i]->outfile == NULL)
	// 		printf("****  NO OUT  >> *****\n");
	// 	else
	// 	{
	// 		k = 0;
	// 		while (cmd[i]->outfile[k]) {
	// 			printf("out ->>%d \t %d |file::%s\n",i,cmd[i]->redirect_out,cmd[i]->outfile[k++]);
	// 		}

	// 	}
	// 	if(cmd[i]->infile == NULL)
	// 		printf("****  NO IN << *****\n");
	// 	else
	// 	{
	// 		k = 0;
	// 		while (cmd[i]->infile[k]) {
	// 			printf("in -<<%d \t %d |file::%s\n",i,cmd[i]->redirect_in,cmd[i]->infile[k++]);
	// 		}
	// 	}
	// 	if(cmd[i]->delemiter == NULL)
	// 		printf("****  NO IN << *****\n");
	// 	else
	// 	{
	// 		k = 0;
	// 		while (cmd[i]->delemiter[k]) {
	// 			printf("in -<<%d \t %d |file::%s\n",i,cmd[i]->redirect_append,cmd[i]->delemiter[k++]);
	// 		}
	// 	}
	// 	if(cmd[i]->herdoc_stdout == NULL)
	// 		printf("****  NO IN << *****\n");
	// 	else
	// 	{
	// 		k = 0;
	// 		while (cmd[i]->herdoc_stdout[k]) {
	// 			printf("in -<<%d \t %d |file::%s\n",i,cmd[i]->herdoc,cmd[i]->herdoc_stdout[k++]);
	// 		}
	// 	}
	// 	printf("--------\n");
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
	return  cmd_rtr;
}

int error_redirect(char **splt)
{
	int i = 0;
	int j = 0;
	while (splt[i] != NULL) {
		printf("{{%s}}\n",splt[i]);
		if(splt[i][0] == '<' || splt[i][0] == '>')
		{
			printf("$$  %s  $$\n",splt[i + 1]);
			if(splt[i + 1] == NULL)
				return 0;
			if(splt[i + 1][0] == '<' || splt[i + 1][0] == '>')
				return 0;
		}
		i++;
	}
	return 1;
}

// int main(int ac,char **av,char **env)
// {
// 	char	*str;
// 	int		i;
// 	char **splt;
// 	t_global_info g_info;
// 	i = 0;
// 	g_info.env_array = env;
// 	while (1)
// 	{
// 		str = readline("Shell->");
// 		add_history(str);
//         splt = lexer(str,env);
// 		if(splt != NULL)
// 			if(!syntx_error_a(splt) || !syntx_error_b(splt))
// 				return 0;;
// 		if (splt != NULL) {
// 			rmplir_strct(splt, &g_info);
// 		}
// 		str = NULL;
// 	}
// }