#include <stdlib.h>
#include "ftsh.h"
#include "init/init.h"
#include <stdio.h>
#include "errors.h"
#include "history/substitution/history_substitutions.h"
#include "history/builtin/history.h"
#include "parse_input/print_syntax_tree.h"
#include "execution/execute_syntax_tree.h"
#include "utils.h"
#include "sig_handler.h"

static void		main_loop(void)
{
	t_shell_env *shell_env;

	shell_env = get_shell_env();
	set_error(NO_ERROR);
	read_input();
	/*if (get_error() != NO_ERROR)
		return ;*/
	if (history_substitution(&shell_env->input_string) <= 0)
	{
		ft_strdel(&shell_env->input_string);
		return ;
	}
	break_input();
	if (shell_env->input_string)
		add_to_history_list(&shell_env->history.list,
				create_history_entry(shell_env->input_string));
	if (get_error() != NO_ERROR)
		return ;
	if (shell_env->input_string)
		ft_strdel(&get_shell_env()->input_string);
	parse_input();
	if (get_error() != NO_ERROR)
		return ;
	execute_command_list(get_shell_env()->syntax_tree);
	delete_command_list(&get_shell_env()->syntax_tree);
}

int				convert_error_to_status(t_error_id id)
{
	if (id == UNEXPECTED_SEMI)
		return (2);
	return (1);
}

int				main(int ac, char **av)
{
	signal(SIGINT, sig_int);
	signal(SIGTSTP, SIG_IGN);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	init(ac, av);
	while (get_shell_env()->should_run)
		main_loop();
	if (get_error() == CHILD_FAILURE || get_last_exit_status())
		return (get_last_exit_status());
	else if (get_error() == NO_ERROR)
		return (EXIT_SUCCESS);
	else
	{
		print_name_and_error(get_error());
		return (convert_error_to_status(get_error()));
	}
}
