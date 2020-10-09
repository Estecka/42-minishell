/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/07 14:12:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../envvar.h"

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <errno.h>

static char* defaultTestSet[] = {
	"PWD",
	"HOME",
	"USER",
	"SHELL",
	"TERM",
	"LOGNAME",
	"bulle",
	NULL
};

extern int main(int argc, char** args, char** environ)
{
	(void)argc;
	(void)args;

	printf("\n\tImported environnement : \n");
	for (char** vars=environ; *vars; vars++)
		printf("%s\n", *vars);

	if (!(environ = envvarinit(environ)))
	{
		printf("Init failed.\n");
		return (-1);
	}
	else
	{
		printf("\n\tDuplicated environnement : \n");
		for (char** vars=environ; *vars; vars++)
			printf("%s\n", *vars);
	}

	printf("\n\tget_env_var()\n");
	for (char** names=defaultTestSet; *names; names++) {
		printf("%s:\t", *names);
		char* value = get_env_var(*names);
		if (!value)
			printf("Errno %d\n", errno);
		else
		{
			printf("\"%s\"\n", value);
			free (value);
		}
	}

	printf("\n\tset_env_var_raw()\n");
	for (char** values = (char*[]){"test=Beep", "test=Boop", "test=Baap", NULL};
		*values;
		values++)
	{
		char* raw = strdup(*values);
		char* rawvalue = strchr(raw, '=') + 1;
		if (!set_env_var_raw(raw))
			printf("[%s] Error\n", raw);
		else {
			char* r = get_env_var("test");
			if (strcmp(r, rawvalue))
				printf("[%s] Got :\t%s\n", rawvalue, r);
			if (r)
				free(r);
		}
	}

	envvardeinit();
	return 0;
}
