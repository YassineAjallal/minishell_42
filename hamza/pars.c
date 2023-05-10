#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <unistd.h>

enum s_cases 
{
	quotes,
	redirects,
};

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int	infile;
	int	outfile;
}		t_mini;

typedef struct s_prompt
{
	t_mini	*cmds;
	char	**envp;
}		t_prompt;

int is_skiped(char s)
{
	if ((s != ' ' || s == '"' || s == '\'') && s != '\0')
	{
		return 1;
	}
	return 0;
}
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
			// printf("\n{{!}}\n");
			line[j++] = '\n';
			line[j++] = str[i];
			line[j++] = str[i + 1];
			line[j++] = '\n';
			i +=2;
		}
		else if(str[i] == '>' && str[i + 1] == '>')
		{
			// printf("\n{{!}}\n");
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
			// printf("{%c}%d\n",str[i],i+1);
			// if (is_skiped(str[i])) {
			// 	// printf("{LOL}\n");
			// 	while (1) {
			// 		int zayd = 0;
			// 		// printf(" %d %c \n",zayd++,str[i]);
			// 		if(str[i] == '"')
			// 		{
			// 			printf("{KK1|%c}\n",str[i]);
			// 			// printf("{qoma}\n");
			// 			if(is_skiped(str[i- 1]))
			// 				i++;
			// 			while (str[i] != '"' && str[i] != '\0') {
			// 				line[j++] = str[i++];
			// 			}
			// 			line[j++] = str[i++];
			// 		}
			// 		// else if(str[i] == '\'')
			// 		// {
			// 		// 	printf("{KK2|%c}\n",str[i]);
			// 		// 	while (str[i] != '\'' && str[i] != '\0') {
			// 		// 		line[j++] = str[i++];
			// 		// 	}
			// 		// 	line[j++] = str[i++];
			// 		// }
			// 		else if(str[i] != ' '){
			// 			printf("{ZAAAABI|%c}\n",str[i]);
			// 			while (str[i] != ' ' && str[i] != '\0') {
			// 				line[j++] = str[i++];
			// 			}
			// 			line[j++] = str[i++];
			// 			// line[j++] = str[i++];
			// 		}
			// 		// printf("'%c|%d'\n",str[i],is_skiped(str[i]));
			// 		// break;
			// 		if(!is_skiped(str[i]))
			// 		{
			// 			printf("IS_skipedf\n");
			// 			break;
			// 		}
			// 	}
				
			// }
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
	i = 0;
	while (splt[i]) {
		printf("%s\n",splt[i]);
		i++;
	}
	printf("\n");
	// printf("%s\n",line);
	return splt;
}

void parser(char **splt,char **env)
{
	int i = 0;
	int expr_ok;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	int cma ;
	int p = 0;
	char *find;
	char *str;
	while (splt[i] != NULL) {
		j = 0;
		cma = 1;
		if(splt[i][0] == '\'')
			cma = 0;
		while (splt[i][j]) {
			k = j;
			expr_ok = 1;
			if(cma != 0)
			{
				if(splt[i][j] == '$')
				{
					str = NULL;
					find = NULL;
					k++;
					while (ft_isalpha(splt[i][k]) && splt[i][k] != '\0') {
						// printf("--%c",splt[i][k]);
						k++;
					}
					// printf("}|%c",splt[i][k-1]);
					k--;
					str = ft_substr(splt[i],j + 1,k - 1);
					str = ft_strjoin(str, "=");
					// printf("\n|%s|\n",str);
					l = 0;
					while (env[l]) {
						if((find = ft_strnstr(env[l], str,ft_strlen(env[l]))))
						{
							expr_ok =0;
							p = 0;
							while (find[p] != '=') {
								p++;
							}
							p++;
							find = ft_substr(find, p, ft_strlen(find));
							printf("%s",find);
						}
					l++;

					}
					// break;
				}
			}
			j = k;
			if(expr_ok == 1)
				printf("%c",splt[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}
#include <stdbool.h> 
typedef struct s_command
{
	int ther;
	char *cmd;
	char *command_path;
	char option;
	char **cmd_parameter;
	bool built_in;
	bool redirect_in;
	bool redirect_out;
	bool redirect_append;
	bool herdoc;
	char *infile;
	char *outfile;
	char *delemiter;
} t_command;

t_command **rmplir_strct(char **splt)
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
	// bax nhseb xhal mn '|' kayna
	while (splt[i] != NULL) {
		if(splt[i][j] == '|')
			cnt++;
		i++;
	}
	cmd = malloc((cnt + 2) * sizeof(t_command *));

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
	//hena ghir affichit cmd dyal kola pipe 
	i = 0;
	printf("---cmd---\n");
	while (cmd[i]->ther != 0) {
		cmd[i]->redirect_in = 0;
		cmd[i]->redirect_out = 0;
		cmd[i]->redirect_append = 0;
		cmd[i]->herdoc = 0;
		cmd[i]->infile = NULL;
		cmd[i]->outfile = NULL;
		cmd[i]->delemiter = NULL;
		printf("===%s\n",cmd[i]->cmd);
		i++;
	}

	i = 0;
	j = 0;
	whr = 0;
	stop = 0;
	// hene fi lowl hsebt xhal kayn mn argument fkola pipe
	printf("----------------------------\n");
	printf("============================\n");
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
	printf("---------parse command----------\n");
	while(cmd[i]->ther)
    {
        j = 0;
        while(cmd[i]->cmd_parameter[j] != NULL)
        {
            printf("%s\n",cmd[i]->cmd_parameter[j++]) ;
        }
        printf("----------\n");
        printf("==========\n");
        i++;
    }
	// hena ghadi nbda n9alb 3la wax kayn redirect o dakxi fi kola pipe

	i = 0;
	j = 0;
	// while(cmd[i].ther)
    // {
    //     j = 0;
    //     while(cmd[i].cmd_parameter[j] != NULL)
    //     {
	// 		printf("{{{%s}}}\n",cmd[i].cmd_parameter[j]);
	// 		if(cmd[i].cmd_parameter[j][0] == '<')
	// 		{
	// 			cmd[i].redirect_in = 1;
	// 			printf("%d ||befor +2 ==  %s\n",i,cmd[i].cmd_parameter[j]);
	// 			j += 1;
	// 			if(cmd[i].cmd_parameter[j])
	// 			{
	// 				printf("%d ||after +2 ==  %s\n",i,cmd[i].cmd_parameter[j]);
	// 				cmd[i].infile = cmd[i].cmd_parameter[j];
	// 				j++;
	// 			}
	// 			else {
	// 				printf("%d   STOP\n",i);
	// 				break;
	// 			}
	// 		}
    //         else if(cmd[i].cmd_parameter[j][0] == '>')
	// 		{
	// 			cmd[i].redirect_out = 1;
	// 			printf("%d ||befor +2 ==  %s\n",i,cmd[i].cmd_parameter[j]);
	// 			j += 1;
	// 			if(cmd[i].cmd_parameter[j])
	// 			{
	// 				printf("%d ||after +2 ==  %s\n",i,cmd[i].cmd_parameter[j]);
	// 				cmd[i].outfile = cmd[i].cmd_parameter[j];
	// 				j++;
	// 			}
	// 			else {
	// 				printf("%d   STOP\n",i);
	// 				break;
	// 			}
	// 		}
	// 		j++;
    //     }
    //     i++;
    // }
	// printf("-------AFFICHE------\n");
	// i = 0;
	// j = 0;
	// while (cmd[i].ther) {
	// 	printf("out ->>%d \t %d |file::%s\n",i,cmd[i].redirect_out,cmd[i].outfile);
	// 	printf("in  ->>%d \t %d |file::%s\n",i,cmd[i].redirect_in,cmd[i].infile);
	// 	printf("--------\n");
	// 	i++;
	// }
	return  cmd;
}

int main(int ac,char **av,char *env[])
{
	char	*str;
	int		i;
	char **splt;
	i = 0;
	while (1)
	{
		str = readline("Shell->");
		add_history(str);
        splt = lexer(str,env);
		// parser(splt,env);
		// rmplir_strct(splt);
		str = NULL;
	}
}