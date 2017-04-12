# include "builtin_def.h"
# include <libft.h>
# include "shell_env.h"
# include "init/init.h"
# include "utils.h"

# define USAGE	"Usage: unset [-fv] name...\n"

int				unset_as(t_variable **env, char *name)
{
	if (env && ft_strlen(name) > 0)
	{
		if (pop_variable_by_name(env, name) == STATUS_SUCCESS)
		{
			return (STATUS_SUCCESS);
		}
	}
	return (STATUS_FAILURE);
}

/*
** If neither -f nor -v is specified, name refers to a variable;
** if a variable by that name does not exist,
** it is unspecified whether a function by that name, if any, shall be unset.
*/

static void 	unset_classic(t_variable **env, char **argv)
{
	size_t	i;

	i = 0;
	while (argv[++i])
	{
		if (!is_an_argument(argv[i]))
			unset_as(env, argv[i]);
	}
}

/*
** If -f is specified, name refers to a function
** and the shell shall unset the function definition.
*/

static void 	unset_option_f(t_variable **env, char **argv)
{
	size_t	i;

	i = 0;
	while (argv[++i])
	{
		if (!is_an_argument(argv[i]) && is_a_function(*env, argv[i]))
		{
			unset_as(env, argv[i]);
		}
	}
}

/*
** If -v is specified, name refers to a variable name
** and the shell shall unset it and remove it from the environment.
** Read-only variables cannot be unset.
*/

static void		unset_option_v(t_variable **env, char **argv)
{
	size_t	i;

	i = 0;
	while (argv[++i])
	{
		if (!is_an_argument(argv[i]) && is_a_variable(*env, argv[i]))
		{
			if (variable_is_overwritable(*env, argv[i]))
				unset_as(env, argv[i]);
		}
	}
}

BUILTIN_RET		builtin_unset(BUILTIN_ARGS)
{
	t_variable	**env;
	char		*opt;

	env = &get_shell_env()->variables;
	opt = get_options_core(argc, argv);
	if (argc > 1)
	{
		if (ft_strchr(opt, 'f'))
			unset_option_f(env, argv);
		else if (ft_strchr(opt, 'v'))
			unset_option_v(env, argv);
		else
			unset_classic(env, argv);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, USAGE);
	}
	free(opt);
	return (STATUS_SUCCESS);
}
