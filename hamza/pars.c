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
	pid_t	pid;
}		t_prompt;


static int	counting(char const *s, char c)
{
	int	i;
	enum s_cases s_c;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		printf("%c",s[i]);
		if (s[i] == '"') {
			i++;
			while (s[i] != '"') {
				i++;
			}
			// if (s[i] != 0)
				cnt++;
		}
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != 0)
				cnt++;
		}
		else
			i++;
	}
	return (cnt + 1);
}

int is_skiped(char s)
{
	if ((s != ' ' || s == '"' || s == '\'') && s != '\0')
	{
		// printf("|%c|",s);
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
			{line[j++] = '\n';
			i++;}
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
	// splt = ft_split(line, '\n');
	printf("%s\n",line);
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
		str = NULL;
	}
}