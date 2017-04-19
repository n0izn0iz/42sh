#ifndef BUILTINS_H
# define BUILTINS_H

#include "variable.h"
#include "opt.h"
/*# include "builtin_args.h"*/

# define STATUS_SUCCESS 0
# define STATUS_FAILURE -1
# define BUILTIN_RET int
# define BUILTIN_ARGS int argc, char **argv

typedef BUILTIN_RET	(*t_builtin)(BUILTIN_ARGS);

BUILTIN_RET 		builtin_cd(BUILTIN_ARGS);
BUILTIN_RET 		builtin_setenv(BUILTIN_ARGS);
BUILTIN_RET 		builtin_unsetenv(BUILTIN_ARGS);
BUILTIN_RET 		builtin_set(BUILTIN_ARGS);
BUILTIN_RET 		builtin_unset(BUILTIN_ARGS);
BUILTIN_RET 		builtin_exit(BUILTIN_ARGS);
BUILTIN_RET			builtin_history(BUILTIN_ARGS);

/*
**
**	SUB BUILTIN
**	
*/

/*
** options
*/
int			retrieve_options(int argc, char **argv, t_opt *o, char *opts);

/*
** setenv, unsetenv
*/
int	 		setenv_as(t_variable **env, char *name, char *value, bool exported);
int 		unsetenv_as(t_variable **env, char *name);
/*
** echo
*/

int			builtin_echo(int argc, char **argv);
bool		escape_char(char *str);
bool		escape(int c);
int			octal(char *c);
int			convert_base(int nbr, int base_from, int base_to);

/*
** env.c
*/
int			builtin_env(int argc, char **argv);
void			exec_env(char **tenv, char **cmd);

#endif
