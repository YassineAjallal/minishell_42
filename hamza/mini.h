#include "../yassine/minishell.h"

char **expand_splt(char **splt,t_global_info g_info);
char **ft_strjoin_2d(char **s1, char *s2);
t_outfile **ft_strjoin_out(t_outfile **s1, char *s2,char *mode);
char *rem_quots(char *splt);
// char *rem_quots(char *splt);
// int syntx_error_a(char **splt);
// int syntx_error_b(char **splt);