#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <unistd.h>

char	*path(char *cmd)
{
	int		rsl;
	char	*path1;
	char	*path2;
	char	*path;

	path1 = "/bin/";
	path2 = "/usr/bin/";
	path = ft_strjoin(path1, cmd);
	rsl = access(path, X_OK);
	if (rsl == 0)
	{
		// printf("%s\n",path);
		return (path);
	}
	path = NULL;
	path = ft_strjoin(path2, cmd);
	rsl = access(path, X_OK);
	if (rsl == 0)
	{
		// printf("%s\n",path);
		return (path);
	}
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
	{
		// printf("%s\n",cmd);
		path = "/bin/bash";
		return (path);
	}
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
	{
		// printf("%s\n",cmd);
		path = "/bin/bash";
		return (path);
	}
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
	{
		// printf("%s\n",cmd);
		path = "/bin/bash";
		return (path);
	}
	return (NULL);
}
void	run_cmd(char **cmd, char *path)
{
	int	pid;
		int status;

	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd, NULL);
		perror(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		// parent process
		waitpid(pid, 0, 0);
	}
}

void	run_echo(char *str)
{
	int		i;
	int		tru;
	int		comma;
	char	chr;
	char	*prn;

	i = 4;
	tru = 0;
	comma = 0;
	chr = 0;
	while (str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		tru = 1;
		i += 2;
		while (str[i] == ' ')
		{
			i++;
		}
	}
	prn = &str[i];
	i = 0;
	while (prn[i])
	{
		if (prn[i] == '"' && !comma)
		{
			comma = 1;
		}
		else if (prn[i] == '\'' && !comma)
		{
			comma = 2;
		}
		else if (prn[i] == '"' && comma == 1)
		{
			comma = 0;
		}
		else if (prn[i] == '\'' && comma == 2)
		{
			comma = 0;
		}
		else
			{printf("%c", prn[i]);}
		i++;
	}
	if(comma)
		perror("dqouate");
	if (tru == 0)
		printf("\n");
}

void run_pwd(char *str)
{
	char pwd[1024];
	// chdir("/path/to/change/directory/to");
	getcwd(pwd, sizeof(pwd));
	printf("%s\n",pwd);
}
void run_env(char *str,char *env[])
{
	int i = 0;
	while (env[i]) {
		printf("%s\n",env[i++]);
	}

}

void run_cd(char *str)
{
	char pwd[1024];
	char *path;
	int rsl;
	getcwd(pwd, sizeof(pwd));
	int i;
	i = 2;
	while (str[i] == ' ' && str[i] != '\0') {
		i++;
	}
	// printf("%s\n",&str[i]);
	path = &str[i];
	printf("%s",path);
	if(chdir(path) != 0)
		perror("cd");
	// printf("%s",path);
}

void	run_implmnt(char *str,char *env[])
{
	char	**splt;
	printf("(%s)\n",str);
	splt = ft_split(str, ' ');
	if (!ft_strncmp(splt[0], "echo", ft_strlen(str)))
	{
		run_echo(str);
	}
	if (!ft_strncmp(splt[0], "pwd", ft_strlen(str)))
	{
		run_pwd(str);
	}
	if (!ft_strncmp(splt[0], "env", ft_strlen(str)))
	{
		run_env(str,env);
	}
	if (!ft_strncmp(splt[0], "cd", ft_strlen(str)))
	{
		run_cd(str);
	}
}
int	main(int ac, char **av,char *env[])
{
	char	**splt;
	char	**str_spcs;
	char	*str;
	char	*pth_cmd;
	int		i;

	splt = malloc(3 * sizeof(char *));
	i = 0;
	while (1)
	{
		str = readline("Shell->");
		add_history(str);
		if (str[0] && str != NULL) 
			run_implmnt(str,env);
		free(str);
		str = NULL;
	}
}
// int main(int ac,char **av)
// {
//     char **splt;
//     char **str_spcs;
//     char *str;
//     splt = malloc(3 * sizeof(char *));
//     char *pth_cmd;
//     int i = 0;
//     while (1) {
//         str = readline("Shell->");
//         add_history(str);
//         if(!ft_strchr(str, ' '))
//         {
//             pth_cmd = path(str);
//             if(!pth_cmd)
//                 perror("zsh");
//             else
//             {
//                 splt[0] =  str;
//                 splt[1] = NULL;
//                 splt[2] = NULL;
//                 // printf("%s \t %s\n",splt[0],splt[1]);
//                 run_cmd(splt,pth_cmd);
//             }
//         }
//         else {
//             str_spcs = ft_split(str, ' ');
//             printf("%s %s\n",str_spcs[0],str_spcs[1]);
//             pth_cmd = path(str_spcs[0]);
//             if (!pth_cmd)
//                 perror("zsh");
//             else
//             {
//                 printf("%s\n",pth_cmd);
//                 splt[0] = str_spcs[0];
//                 splt[1] = str_spcs[1];
//                 splt[2] = NULL;
//                 run_cmd(splt, pth_cmd);
//             }
//         }
//         free(str);
//     }
// }