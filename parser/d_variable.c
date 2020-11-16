#include "parser_internals.h"
#include <stdio.h>
#include "../libft/libft.h"
#include "../envvar/envvar.h"
#include "../builtin/builtins.h"

void			ch_envvar(int sp, char out)
{
	int i;
	int j;
	char **env;

	i = 0;
    j = 0;
	env = g_envarray.content;
	while (env[i])
	{
        j = 0;
		while (env[i][j])
		{
			if ((sp && ft_isspace(env[i][j])) || env[i][j] == -10)
				env[i][j] = out;
			j++;
		}
		i++;
	}
}

int count_wd(char *args)
{
    int i;
    int cmpt;
    char *tmp;

    i = 0;
    cmpt = (*args) ? 1 : 0;
    while ((tmp = ft_strchr(args, -10)))
    {
        ++cmpt;
        while (tmp[i] == -10)
            i++;
        args = &tmp[i + 1];
    }
    return (cmpt);
}

char    **ft_copyargs(char **args, char **splt, int wd, int limit)
{
    int size;
    int i;
    int j;
    char **tmp;

    size = 0;
    i = 0;
    j = 0;
    while (args[i++])
        size++;
    tmp = malloc(sizeof(char*) * (wd + size));
    i = 0;
    while (args[i])
    {
        if (i < limit || j >= wd) 
        {
            tmp[i + j] = ft_strdup(args[i]);
            i++;
        }
        else if (j < wd)
        {   
            while (j < wd) 
            { 
                tmp[i + j] = ft_strdup(splt[j]);
                j++;
            }
            i++;
        }
    }
    tmp[i + j] = NULL;
    free_mtab(&args);
   return (tmp);
}

char**    post_varproc(char **args)
{
    int i = 0;
    char **splt;
    int wd;

    wd = 0;
    i = 0;
    while (args[i])
    { 
        if (ft_strchr(args[i], -10) && (wd = count_wd(args[i])))
        {
            splt = ft_split(args[i], -10);
            args = ft_copyargs(args, splt, wd, i);
        }
        i++;
    }
    return (args);
}