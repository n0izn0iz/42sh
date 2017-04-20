#include "shell_env.h"
#include "init/init.h"
#include "read_input/editor/editor.h"
#include "abstract_list.h"
#include "history/builtin/history.h"
#include "errors.h"
#include "utils.h"

static void	init_variables_list(t_shell_env *shell_env)
{
	extern char	**environ;
	char		**line;
	t_variable	*var;
	size_t		i;

	i = -1;
	while (environ[++i])
	{
		line = ft_strsplit(environ[i], '=');
		if (line && ft_tablen(line) == 2 &&
			ft_strlen(line[0]) > 0 && ft_strlen(line[1]) > 0)
		{
			var = create_variable(line[0], line[1], true);
			list_push_back((t_abstract_list**)&shell_env->variables\
				, (t_abstract_list*)var);
		}
		ft_freetabchar(line);
	}
}

static char	*get_path_to_ftsh(char const *ftsh_name)
{
	char		*cwd;

	if (ftsh_name == NULL)
		fatal_error("NULL ptr fed to get_path_to_ftsh()");
	if (ftsh_name[0] == '/')
		return (ft_strdup(ftsh_name));
	if (ftsh_name[0] == '.' && ftsh_name[1] == '/')
		ftsh_name += 2;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		fatal_error("getcwd(NULL, 0) failed in get_path_to_ftsh()");
	return (ft_strjoinf(cwd, ft_strjoin("/", ftsh_name), 3));
}

void	init(int ac, char **av)
{
	t_shell_env		*shell_env;

	set_error(NO_ERROR);
	shell_env = get_shell_env();
	ft_bzero(shell_env, sizeof(t_shell_env));
	ft_bzero(&shell_env->history, sizeof(t_sh_history));
	shell_env->path_to_42sh = get_path_to_ftsh(av[0]);
	init_variables_list(shell_env);
	parse_options(ac, av, shell_env);
	load_history(shell_env, HISTFILE, 0);
	shell_env->should_run = true;
}
