/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/10/21 12:00:10 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>

/*
** A breakdown of a single process.
** @var unsigned int argc	The amount of arguments in `args`.
** @var char** args	The arguments passed to the process, this includes the exec
** utable's name.
** t_procexpr* pipein	The process expression that pipes into this.
** t_procexpr* pipeout	The process expression this pipes into.
** @var char** inputs	An array of pathes to the input files.
** 	This array is null-terminated.
** @var char** outputs	An array of pathes to the output files.
** 	This array is null-terminated.
** @var short* outtypes	For each output, whether this redirection is truncate (
** TRUE) or append (FALSE).
** 	This array is not NULL-terminated, but has the same length as `outputs` (mi
** nus the null terminator);
*/

typedef struct s_procexpr	t_procexpr;
struct		s_procexpr
{
	unsigned int	argc;
	char			**args;

	t_procexpr		*pipein;
	t_procexpr		*pipeout;

	char			**inputs;
	char			**outputs;
	short			*outtypes;
};

/*
** Parses all commands in the given line.
** This will overwrite errno, even in case of sucess !
** The arguments of the command aren't fully processed at this points, they wil
** l still contain ariable names, and the escape sequences "\\" and "\$".
** @param char* line	The full line that contains the commands.
** @return t_procexpr*	An array of command expressions, or NULL in case of err
** or.
*/

t_procexpr	**get_next_cmdline(const char *line);

/*
** Parses a raw argument into its final form.
** This involves replacing variables name, escaped characters, and quotes.
** @param const char* arg	The raw argument to parse.
** @return char*	An allocated copy of the parsed argument, or NULL in case of error
*/

char 		*postproc_arg(const char *arg);

/*
** Process all arguments from an array jus as `postproc_arg` would.
** @param char** args	A null-terminated array of argument to process.
** 	The argument are processed in-place.
*/

void		postproc_args_all(char **args);

/*
** Recursively frees a process expression, all of its components and chained pr
** ocesses.
** @param t_procexpr* expr	The expression to destroy.
*/

void		procexpr_destroy(t_procexpr *expr);

/*
** Destroys all process expressions in an array, and the array itself.
** @param t_procexpr* exprarray	The array to destroy.
** 	This is expected to be a valid array of valid t_procexpr.
*/

void	procexpr_destroy_all(t_procexpr **exprarray);

/*
** Destroys n command expressions from an array.
** @param t_procexpr** array	A pointer to the array.
** @param size_t lenght	The length of the array.
*/

void		procexpr_destroyarrayn(t_procexpr **array, size_t length);


/*
** Fonction to be defined in another module, used in postproc_arg.
** @param const char* name	The name of an environnement variable.
** @param char*	A copy of the variable's value.
** @return char*	The variable's value, or NULL in case of error.
*/

extern char	*get_env_var(const char *name);

#endif
