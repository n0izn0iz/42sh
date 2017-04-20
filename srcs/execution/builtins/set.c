# include "builtin_def.h"
# include <libft.h>
# include <signal.h>
# include "shell_env.h"
# include "abstract_list.h"
# include "init/init.h"

# define FORBIDDEN_CHAR	"Is forbidden to use the character '='\n"
# define USAGE 			"Usage: set <key> <value>\n"

BUILTIN_RET		builtin_set(BUILTIN_ARGS)
{
	(void)envp;
	t_variable	**env;

	env = &get_shell_env()->variables;
	if (argc == 1)
	{
		display_variables(false);
		return (STATUS_SUCCESS);
	}
	else if (argc == 2 || argc == 3)
	{
		if (ft_strchr(argv[1], '='))
		{
			ft_dprintf(STDERR_FILENO, FORBIDDEN_CHAR);
			return (STATUS_FAILURE);
		}
		if (argc == 2)
		{
			if (setenv_as(env, argv[1], "", false) == STATUS_SUCCESS)
				return (STATUS_SUCCESS);
		}
		else
		{
			if (setenv_as(env, argv[1], argv[2], false) == STATUS_SUCCESS)
				return (STATUS_SUCCESS);
		}
	}
	else
	{
		ft_dprintf(STDERR_FILENO, USAGE);
	}
	return (STATUS_FAILURE);
}

