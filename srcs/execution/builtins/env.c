#include "builtins.h"
#include "utils.h"
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
*/

int	builtin_env(int argc, char **argv, char **envp)
{
	char		**tenv;
	char		*opt;

	if ((opt = get_options_core(argc, argv)) == (char *)-1)
		return (STATUS_FAILURE);
	if (ft_strchr(opt, 'i') != NULL)
	{
		tenv = (char**)memalloc_or_die(sizeof(char*));
		tenv[0] = NULL;
	}
	else
		tenv = ft_tabdup(envp);
	ft_strdel(&opt);
	run_env(argc, argv, tenv);
	ft_freetabchar(tenv);
	return (STATUS_SUCCESS);
}

/*
** pass options
** add env var specified as argument
** if arrived to last argument (no exec found): display env var
** else: execute last arguments with options
*/

void	run_env(int argc, char **argv, char **tenv)
{
	int		i;

	i = 0;
	while (i < argc && argv[i][0] == '-')
		i++;
	while (i < argc && ft_strchr(argv[i], '=') != NULL)
	{
		tenv = ft_setenv(tenv, argv[i]);
		i++;
	}
	if (i == argc)
		ft_puttab(tenv);
	else
		exec_env(tenv, &argv[i]);
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
