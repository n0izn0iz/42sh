#include "builtins.h"
#include "variable.h"
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

static char			*get_path(int argc, char **argv)
{
	if (argc == 1)
		return (get_variable("HOME"));
	else
	{
		if (ft_strequ(argv[1], "-"))
			return (get_variable("OLDPWD"));
		else
			return (ft_strdup(argv[1]));
	}
}

BUILTIN_RET 		builtin_cd(BUILTIN_ARGS)
{
	(void)envp;
	int		ret;
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	new_pwd = get_path(argc, argv);
	if (new_pwd != NULL)
	{
		ret = chdir(new_pwd);
		if (ret == 0)
		{
			set_variable("OLDPWD", old_pwd);
			free(old_pwd);
			free(new_pwd);
			new_pwd = getcwd(NULL, 0);
			set_variable("PWD", new_pwd);
			free(new_pwd);
			return (STATUS_SUCCESS);
		}
	}
	ft_putendl_fd("42sh: some error with cd", 2);
	return (-1);
}
