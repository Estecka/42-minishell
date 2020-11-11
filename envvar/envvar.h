/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:51:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/11 19:43:38 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVVAR_H
# define ENVVAR_H

# include "../dynarray/dynarray.h"

t_dynarray	g_envarray;
char		***g_environ;

/*
** Duplicates the provided array to initialize the environnement.
** @param char** environ	An array of strings that will be used as environnem
** ent variables. These are not checked for invalid syntax.
** @param char**	The resulting environnement, or NULL in case of error.
*/

char		**envvarinit(char **environ);

/*
** Frees all the internal pointers of the environnement.
*/

void		envvardeinit(void);

/*
** Checks whether an environnement variable exists
** @param const char* name	The name of the variable to check.
** @return bool	true if the variable exists.
*/

short		isset_envvar(const char *name);

/*
** Fetches the value of an environnement variable.
** @param const char* name	The name of the variable to get.
** @return const char*	A pointer to the value of the variable. NULL if the vari
** able is not set, or a pointer to `\0` if the variable exists but is empty.
** 	This pointer is managed internally and does not need to be freed.
** 	The pointed memory is volatile and may be freed if the variables value is ch
** 	anged later on.
*/

const char	*get_envvar_rdonly(const char *name);

/*
** Fetches the value of an environnement variable.
** @param const char* name	The name of the variable to get.
** @return char*	An allocated copy of the variable's value.
*/

char		*get_env_var(const char *name);

/*
** Sets an environnement variable.
** @param char* value 	A string formated as "name=value".
** 	This string is NOT checked for invalid syntax.
** 	This exact pointer is stored internally, and should notbe modified or freed
**  afterward.
** @return bool
** 	true 	OK;
** 	false 	Error;
*/

short		set_env_var_raw(char *value);

/*
** Sets an environnement variable.
** @param const char* name	The name of the variable to set.
** 	This name is NOT checked for invalid caracters, except for '='.
** @param const char* value	The value to set.
** return bool
** 	true 	OK
** 	false	Error
*/

short		set_env_var(const char *name, const char *value);

/*
** Checks the validity of an environnement variable's name.
** The special name '?' is considered valid.
** @param const char* name	The name to validate
** @return char*	A pointer to the first invalid character, else a pointer to
**  the null terminator.
*/

char		*validate_var_name(const char *name);

/*
** delete a variable of g_envarray.content and update his lenght
*/
int			envclear(char *delet);
void		shell_level(void);
char		**envnulinit(void);
#endif
