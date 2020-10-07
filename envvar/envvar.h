/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:51:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/07 13:51:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVVAR_H
# define ENVVAR_H

/*
** Fetches the value of an environnement variable.
** @param const char* name	The name of the variable.
** @return char*	An allocated copy of the variable's value.
*/

char		*get_env_var(const char *name);

/*
** Sets an environnement variable.
** @param const char* name
** @param const char* value
** @return bool
** 	true 	OK
** 	false	Error
*/

short		set_env_var(const char *name, const char *value);

#endif
