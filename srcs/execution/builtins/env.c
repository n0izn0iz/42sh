#include "builtins.h"
#include "opt.h"
#include "libft.h"
#include "shell_env.h"
#include "../../tabenv.h"
#include "../exec.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <paths.h>

/*
** retrive '-i' option
** if '-i' empty var env, retrive current env var
** transform env var from linked list to tab
** add env var specified as argument
** display env var if no 
** execute last argument
*/

int	builtin_env(int argc, char **argv)
{
	t_opt		*o;
	int		i;
	char		**tenv;

	o = (t_opt*)memalloc_or_die(sizeof(t_opt));
	i = retrieve_options(argc, argv, o, "i");
	if (o->i == false)
		tenv = get_variables_for_execution(get_shell_env()->variables);
	else
	{
		tenv = (char**)memalloc_or_die(sizeof(char*));
		tenv[0] = NULL;
	}
 	free(o);
	while (++i < argc && ft_strchr(argv[i], '=') != NULL)
		tenv = ft_setenv(tenv, argv[i]);
	if (i == argc)
		ft_puttab(tenv);
	else
		exec_env(tenv, &argv[i]);
	ft_freetabchar(tenv);
	return (STATUS_SUCCESS);
}

/*
** Retrieve PATH, if doesn't exist, take default values
** fork, execute, wait, free
*/

void	exec_env(char **tenv, char **cmd)
{
	char		*spath;
	char		**path;

	if ((spath = ft_strdup(get_tenv(tenv, "PATH"))) == NULL)
		spath = ft_strdup(_PATH_DEFPATH);
	path = ft_strsplit(spath, ':');
	ft_strdel(&spath);
	if (fork() == 0)
		execute(cmd, tenv, path);
	wait(NULL);
	ft_freetabchar(path);
}
