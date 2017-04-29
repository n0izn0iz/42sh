#include "execute_syntax_tree.h"
#include "utils.h"
#include <libft.h>
#include "variable.h"
#include <stdio.h>

static char		*get_backup_var(t_variable *env_backup, char *name)
{
	t_variable	*env;
	char		*val;

	val = NULL;
	env = get_shell_env()->variables;
	get_shell_env()->variables = env_backup;
	val = get_variable(name);
	if (!val && variable_exist(env_backup, name))
		val = ft_strnew(1);
	get_shell_env()->variables = env;
	return (val);
}

static void		set_env_exec(t_variable **env_backup, t_variable *assignments)
{
	*env_backup = copy_variable(get_shell_env()->variables);
	set_assignments(assignments, true);
}

static void		restore_env(t_variable **env_backup, t_variable *assignments)
{
	char		*val;

	while (assignments)
	{
		val = get_backup_var(*env_backup, assignments->name);
		if (val)
			setenv_as(&get_shell_env()->variables, assignments->name, val, true);
		else
			unsetenv_as(&get_shell_env()->variables, assignments->name);
		ft_strdel(&val);
		assignments = assignments->next;
	}
	delete_all_variables(env_backup);
}

t_error_id		execute_builtin(t_simple_command *cmd, size_t lvl)
{
	t_error_id				ret;
	t_builtin_def const		*builtin;
	t_variable				*env_backup;
	(void)lvl;

	ret = NO_ERROR;
	if (cmd != NULL)
	{
		set_variable("_", cmd->argv[0], false);
		if (cmd->argv[0] && ft_strcmp(cmd->argv[0], "exit"))
			set_env_exec(&env_backup, cmd->assignments);
		if (ft_strcmp(cmd->argv[0], "env") == 0)
			ret = builtin_env(ft_tablen(cmd->argv), cmd->argv, cmd);
		else
		{
			builtin = get_matching_builtin(cmd->argv[0]);
			if (builtin == NULL)
				return (NO_SUCH_BUILTIN);
			#ifdef FTSH_DEBUG
			print_n_char_fd(' ', (lvl) * 2, 2);
			dprintf(2, "executing builtin %s\n", builtin->name);
			#endif
			if (builtin->builtin == NULL)
			{
			#ifdef FTSH_DEBUG
				print_n_char_fd(' ', (lvl + 1) * 2, 2);
				dprintf(2, "%s is undefined\n", builtin->name);
			#endif
				return (NO_SUCH_BUILTIN);
			}
			ret = builtin->builtin(ft_tablen(cmd->argv), cmd->argv);
			set_variable("_", cmd->argv[ft_tablen(cmd->argv) - 1], false);
			#ifdef FTSH_DEBUG
			print_n_char_fd(' ', (lvl) * 2, 2);
			dprintf(2, "done executing builtin %s, %s\n", builtin->name, ret == NO_ERROR ? "ok" : "error");
			#endif
		}
	}
	restore_env(&env_backup, cmd->assignments);
	set_last_exit_status(ret == NO_ERROR ? 0 : 1);
	return (ret);
}
