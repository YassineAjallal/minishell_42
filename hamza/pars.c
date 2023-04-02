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
char **lexer(char *str,char **env)
{
    int i = 0;
	char *line;
	int j = 0;
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
	// printf("%s\n",line);
	return splt;
}

void parser(char **splt,char **env)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	char *find;
	char *str;
	while (splt[i] != NULL) {
		j = 0;
		while (splt[i][j]) {
			k = j;
			if(splt[i][j] == '$')
			{
				str = NULL;
				find = NULL;
				k++;
				while (splt[i][k] != ' ' && splt[i][k] != '\0') {
					// printf("%c",splt[i][k]);
					k++;
				}
				str = ft_substr(splt[i],j + 1,k);
				l = 0;
				while (env[l]) {
					if((find = ft_strnstr(env[l], str,ft_strlen(env[l]))))
						printf("%s",find);
				l++;
					
				}
				// printf("%s",str);
				// printf("$");
				break;
			}
			j = k;
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
		parser(splt,env);
		str = NULL;
	}
}