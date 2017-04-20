#include "execute_syntax_tree.h"
#include "utils.h"
#include <libft.h>

#include <stdio.h>

t_error_id	execute_builtin(t_simple_command *cmd, size_t lvl)
{
	t_error_id				ret;
	t_builtin_def const		*builtin;
	char		**env;

	ret = NO_ERROR;
	if (cmd != NULL)
	{
		builtin = get_matching_builtin(cmd->argv[0]);
		if (builtin == NULL)
			return (NO_SUCH_BUILTIN);
		print_n_char_fd(' ', (lvl) * 2, 2);
		dprintf(2, "executing builtin %s\n", builtin->name);
		if (builtin->builtin == NULL)
		{
			print_n_char_fd(' ', (lvl + 1) * 2, 2);
			dprintf(2, "%s is undefined\n", builtin->name);
			return (NO_SUCH_BUILTIN);
		}
		env = get_variables_for_execution(cmd->assignments);
		ret = builtin->builtin(ft_tablen(cmd->argv), cmd->argv, env);
		ft_freetabchar(env);
		print_n_char_fd(' ', (lvl) * 2, 2);
		dprintf(2, "done executing builtin %s, %s\n", builtin->name, ret == NO_ERROR ? "ok" : "error");
	}
	return (ret);
}
