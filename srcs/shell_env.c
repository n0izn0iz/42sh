#include "shell_env.h"

t_shell_env			*get_shell_env(void)
{
	static t_shell_env	shell_env;
	return (&shell_env);
}
