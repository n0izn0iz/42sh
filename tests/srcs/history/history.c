#include <libft.h>
#include "test_utils.h"

#include "shell_env.h"
#include "history.h"
#include "ftsh.h"

#define HIST_TESTFILE "history_test_file"

void	initialize_history()
{
	char *av[] = {"42sh"};
	init(1, av);
	load_history(get_shell_env(), HIST_TESTFILE);

	#ifdef BANG_TEST_VERBOSE
	ft_putendl("\nCurrent history list: ");
	print_history(get_shell_env()->history, 0);
	#endif
}

/*
	no ret value for builtins for the moment
*/

void	history_print()
{
	char	*av[] = {"history"};
	// int ret;

	builtin_history(1, av);
	// CU_ASSERT_EQUAL(ret, 0)

}

void	history_print_offset()
{
	char	*av[][2] = {
						{"history", "0"},
						{"history", "3"}
					};
	// int ret;

	builtin_history(2, av[0]);
	// CU_ASSERT_EQUAL(ret, 0)
	builtin_history(2, av[1]);
	// CU_ASSERT_EQUAL(ret, 0)

}

void	history_delete()
{
	t_history *saved;

	char	*av[][3] = {
						{"history", "d3", NULL},
						{"history", "d", "3"}
					};

	saved = get_shell_env()->history->next->next;
	builtin_history(2, av[0]);
	CU_ASSERT_PTR_NOT_EQUAL(get_shell_env()->history->next->next, saved);
	builtin_history(3, av[1]);
}

void	history_to_file()
{
	/*
		still don't get the difference between options a & w
	*/
	char	*av[][3] = {
						{"history", "-w", NULL},
						{"history", "-a", NULL},
						{"history", "-a", "test"}
					};

	builtin_history(2, av[0]);
	builtin_history(2, av[1]);
}

void	history_clear()
{
	char *av[] = {"history", "-c"};

	builtin_history(2, av);
	CU_ASSERT_PTR_NULL(get_shell_env()->history);
}

void	history_errors()
{
	char	*av[][3] = {
						{"history", "-l", NULL},
						{"history", "l", NULL},
						{"history", "3", "coucou"},
						{"history", "-d", "slijg"},
						{"history", "-d", "8797"}
						};

	builtin_history(2, av[0]);
	// builtin_history(2, av[1]);
	// builtin_history(3, av[2]);
	builtin_history(3, av[3]);
	builtin_history(3, av[4]);


}
