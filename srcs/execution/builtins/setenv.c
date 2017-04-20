# include "builtin_def.h"
# include <libft.h>
# include <signal.h>
# include "shell_env.h"
# include "abstract_list.h"
# include "variable.h"

# define FORBIDDEN_CHAR	"Is forbidden to use the character '='\n"
# define USAGE 			"Usage: setenv <key> <value>\n"

BUILTIN_RET		builtin_setenv(BUILTIN_ARGS)
{
	(void)envp;
	t_variable	**env;

	env = &get_shell_env()->variables;

	if (argc == 2 || argc == 3)
	{
		if (ft_strchr(argv[1], '='))
		{
			ft_dprintf(STDERR_FILENO, FORBIDDEN_CHAR);
			return (STATUS_FAILURE);
		}
		if (argc == 2)
		{
			if (setenv_as(env, argv[1], "", true) == STATUS_SUCCESS)
				return (STATUS_SUCCESS);
		}
		else
		{
			if (setenv_as(env, argv[1], argv[2], true) == STATUS_SUCCESS)
				return (STATUS_SUCCESS);
		}
	}
	else
	{
		ft_dprintf(STDERR_FILENO, USAGE);
	}
	return (STATUS_FAILURE);
}

int			setenv_as(t_variable **env, char *name, char*value, bool exported)
{
	if (env && ft_strlen(name) > 0)
	{
		if (variable_exist(*env, name))
		{
			if (variable_is_overwritable(*env, name))
				unsetenv_as(env, name);
			else
				return (STATUS_SUCCESS);
		}
		list_push_back((t_abstract_list**)&env,
			(t_abstract_list*)create_variable(name, value, exported));
		return (STATUS_SUCCESS);
	}
	return (STATUS_FAILURE);
}
