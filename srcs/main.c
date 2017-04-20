#include <stdlib.h>
#include "ftsh.h"
#include "init/init.h"
#include <stdio.h>
#include "errors.h"
#include "history/substitution/history_substitutions.h"
#include "history/builtin/history.h"
#include "parse_input/print_syntax_tree.h"
#include "execution/execute_syntax_tree.h"

#include "utils.h" //remove

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
	add_to_history_list(&shell_env->history.list, create_history_entry(shell_env->input_string));
	if (get_error() != NO_ERROR)
		return ;
	ft_strdel(&get_shell_env()->input_string);
	parse_input();
	if (get_error() != NO_ERROR)
		return ;
	execute_command_list(get_shell_env()->syntax_tree);
	delete_command_list(&get_shell_env()->syntax_tree);
}

int				main(int ac, char **av)
{
	////////// TEST GET OPTION ////////////
	// char	*tmp = get_options_core(ac, av);
	// ft_dprintf(2, "ALL ARGUMENT \"%s\"\n", tmp);
	// int i = 0;
	// while (av[++i])
	// {
	// 	if (is_an_option(av, i))
	// 		ft_dprintf(2, "   OPT%d \"%s\"\n", i, av[i]);
	// 	else
	// 		ft_dprintf(2, "NO OPT%d \"%s\"\n", i, av[i]);
	// }
	// ft_dprintf(2, "NB ARG: %d\n", number_of_argument(av));
	// return (0);
	///////////////////////////////////////

	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	init(ac, av);
	while (get_shell_env()->should_run)
		main_loop();
	print_name_and_error(get_error());
	if (get_error() == NO_ERROR)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
