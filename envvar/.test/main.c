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

#include <stdio.h>

extern int main(int argc, char** args, char** environ)
{
	(void)argc;
	(void)args;

	printf("\n\tImported environnement : \n");
	for (char** vars=environ; *vars; vars++)
		printf("%s\n", *vars);

	return 0;
}
