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

	printf("\n\tset_var && get_var\n");
	char*** testvars = (char**[]){
		(char*[2]){"test", "a"},
		(char*[2]){"test", "b"},
		(char*[2]){"test", "c"},
		(char*[2]){"fishtre", "douille"},
		NULL
	};
	for ((void)testvars; *testvars; testvars++)
	{
		#define TESTVARKEY ((*testvars)[0])
		#define TESTVARVAL ((*testvars)[1])
		if (!set_env_var(TESTVARKEY, TESTVARVAL))
		{
			printf("Set(%s, %s) : Errno %d\n", TESTVARKEY, TESTVARVAL, errno);
			continue;
		}
		char* r = get_env_var(TESTVARKEY);
		if (!r)
			printf("Get(%s) : Errno %d\n", TESTVARKEY, errno);
		else if (strcmp(r, TESTVARVAL))
			printf("Get(%s) : Expected \"%s\" Got \"%s\"", TESTVARKEY, TESTVARVAL, r);
		if (r)
			free(r);
	}

	envvardeinit();

	printf("Done.\n");
	return 0;
}
