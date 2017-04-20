# include "builtin_def.h"
# include <libft.h>
# include "shell_env.h"
# include "init/init.h"

# define FORBIDDEN_CHAR	"Is forbidden to use the character '='\n"
# define USAGE 			"Usage: unsetenv <key> ...\n"

BUILTIN_RET		builtin_unsetenv(BUILTIN_ARGS)
{
	(void)envp;
	t_variable	**env;
	size_t		i;

	env = &get_shell_env()->variables;
	if (argc > 1)
	{
		i = 0;
		while (argv[++i])
		{
			if (unsetenv_as(env, argv[i]) == STATUS_FAILURE)
			{
				return (STATUS_FAILURE);
			}
		}
		return (STATUS_SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, USAGE);
	}
	return (STATUS_FAILURE);
}

int				unsetenv_as(t_variable **env, char *name)
{
	if (env && ft_strlen(name) > 0)
	{
		if (ft_strchr(name, '='))
		{
			ft_dprintf(STDERR_FILENO, FORBIDDEN_CHAR);
			return (STATUS_FAILURE);
		}
		if (pop_variable_by_name(env, name) == STATUS_SUCCESS)
		{
			return (STATUS_SUCCESS);
		}
	}
	return (STATUS_FAILURE);
}
