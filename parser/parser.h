/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/10/28 14:14:04 by abaur            ###   ########.fr       */
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
** The arguments of the command aren't fully processed at this points, they will
**  still contain ariable names, and the escape sequences "\\" and "\$".
** @param char* line	The full line that contains the commands.
** @return t_procexpr*	An array of command expressions, or NULL in case of erro
** r.
*/

t_procexpr	**get_next_cmdline(const char *line);

/*
** Process all arguments from an array jus as `postproc_arg` would.
** @param char** args	A null-terminated array of argument to process.
** 	The argument are processed in-place.
*/

void		postproc_args_all(char **args);

/*
** Measures the amount of processes in a chain of pipes.
** @param t_procexpr* expr	The first process expression in the chain.
** @return int	The total amount of processes.
*/

int			procexpr_pipelen(t_procexpr *expr);

/*
** Recursively frees a process expression, all of its components and chained pro
** cesses.
** @param t_procexpr* expr	The expression to destroy.
*/

void		procexpr_destroy(t_procexpr *expr);

/*
** Destroys all process expressions in an array, and the array itself.
** @param t_procexpr* exprarray	The array to destroy.
** 	This is expected to be a valid array of valid t_procexpr.
*/

void		procexpr_destroy_all(t_procexpr **exprarray);

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
