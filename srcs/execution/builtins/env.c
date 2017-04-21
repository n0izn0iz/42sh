#include "utils.h"
#include "../execute_pipeline.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <paths.h>

/*
** retrive '-i' option
** if '-i' empty var env, set e as NULL
** else: retrive current env var
** do a backup of env var
** use new env
** restore previous env var
*/

BUILTIN_RET	builtin_env(BUILTIN_ARGS)
{
	char		*opt;
	t_variable	*e;
	t_variable	*save;

	if ((opt = get_options_core(argc, argv)) == (char *)-1)
		return (STATUS_FAILURE);
	e = ft_strchr(opt, 'i') != NULL ? NULL : \
		copy_variable(get_shell_env()->variables);
	save = get_shell_env()->variables;
	ft_strdel(&opt);
	get_shell_env()->variables = e;
	run_env(argc, argv, cmd);
	delete_all_variables(&e);
	get_shell_env()->variables = save;
	return (STATUS_SUCCESS);
}

/*
** pass options
** add env var specified as argument
** if not last arg: execute last arguments with options: mv position of exec
** else: display env var
*/

void		run_env(BUILTIN_ARGS)
{
	int	i;
	char	**split;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] == 'i')
		i++;
	while (i < argc && ft_strchr(argv[i], '=') != NULL)
	{
		split = ft_strsplit(argv[i], '=');
		setenv_as(&get_shell_env()->variables, split[0], split[1],\
			 false);
		ft_freetabchar(split);
		i++;
	}
	if (argc > i)
	{
		cmd->argv = &(cmd->argv[i]);
		execute_simple_command(cmd, 0);
	}
	else
		display_variables(false);
}
