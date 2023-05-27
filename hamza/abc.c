#include <stdbool.h> 
#include <stdlib.h> 
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
int main() {
  t_command *cmd;
  char **splt;
  int i = 0;
  int j = 0;
  int cnt = 0;
  int whr = 0;
  int k = 0;
  int strt = 0;
  splt = malloc(6 * sizeof(char *));
  splt[0] = "echo";
  splt[1] = "oui";
  splt[2] = "|";
  splt[3] = "echo";
  splt[4] = "no";
  splt[5] = NULL;
  while (splt[i] != NULL) {
        if(splt[i][j] == '|')
            cnt++;
        i++;
  }
  cmd = malloc((cnt + 2) * sizeof(t_command));
  i = 0;
  j= 0;
  k = 0;
  strt = 0;
  whr = 0;
  cnt = 0;
  while (splt[i] != NULL) {
        if(strt == 0)
        {
            cmd[whr].ther = 1;
            cmd[whr].cmd = splt[i];
            strt = 1;
            whr++;
        }
        if (splt[i][0] == '|') 
            strt = 0;
        i++;
    }
  i = 0;
  j= 0;
  k = 0;
  strt = 0;
  whr = 0;
  cnt = 0;
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
        cmd[whr].cmd_parameter = malloc(sizeof(char *) * (cnt + 1));
        i = k;
        if (splt[i] == NULL) 
            break;
        i++;
        whr++;
    }
    i = 0;
    j = 0;
    whr = 0;
    k = 0;
    while (splt[i]) {
        if(splt[i][0]  != '|')
        {
            cmd[k].cmd_parameter[j++] = splt[i];
            // j++;
        }
        else{
            cmd[k].cmd_parameter[j] = NULL;
            j = 0;
            k++;
        }
        i++;
        if(splt[i]  == NULL)
            cmd[k].cmd_parameter[j] = NULL;
    }
    i = 0;
    j = 0;
    while(cmd[i].ther)
    {
        j = 0;
        while(cmd[i].cmd_parameter[j] != NULL)
        {
            printf("%s\n",cmd[i].cmd_parameter[j++]) ;
        }
        printf("----------\n");
        printf("==========\n");
        i++;
    }
  return 0;
}