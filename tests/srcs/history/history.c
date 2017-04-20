#include <libft.h>
#include "test_utils.h"

#include "shell_env.h"
#include "history/builtin/history.h"
#include "ftsh.h"
#include "abstract_list.h"


// #define HISTORY_TEST_VERBOSE

void	initialize_history()
{
	char *av[] = {"42sh"};
	init(1, av);
	load_history(get_shell_env(), HISTFILE, 0);

	#ifdef HISTORY_TEST_VERBOSE
	ft_printf("\nHistory list has been initialized from %s: \n", HISTFILE);
	print_history(get_shell_env()->history.list, 0);
	#endif
}

/*
	no ret value for builtins for the moment
*/

void	history_add_one()
{
	t_history *history;
	char	str[] = "added\n";
	size_t 	nb;

	history = get_shell_env()->history.list;
	nb = list_count((t_abstract_list *)history);
	add_to_history_list(&history, create_history_entry(str));
	CU_ASSERT_EQUAL(nb + 1, list_count((t_abstract_list *)history));
	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history after adding entry \"added\":");
		print_history(history, 0);
	#endif
}

void	history_print()
{
	char	*av[] = {"history"};
	// int ret;

	builtin_history(1, av, NULL);
}

void	history_print_offset()
{
	char	*av[][2] = {
						{"history", "0"},
						{"history", "3"}
					};
	// int ret;

	builtin_history(2, av[0], NULL);
	// CU_ASSERT_EQUAL(ret, 0)
	builtin_history(2, av[1], NULL);
	// CU_ASSERT_NOT_EQUAL(get_error(), 0);

}

void	history_delete()
{
	size_t nb;

	char	*av[][3] = {
						{"history", "-d7", NULL},
						{"history", "-d", "1"}
					};

	nb = list_count((t_abstract_list *)get_shell_env()->history.list) - 1;
	//printf("nb: %zu\n", nb);
	builtin_history(2, av[0], NULL);
	CU_ASSERT_EQUAL(nb, list_count((t_abstract_list *)get_shell_env()->history.list));
	nb--;

	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history after deleting entry 7:");
		print_history(get_shell_env()->history.list, 0);
	#endif

	builtin_history(3, av[1], NULL);
	CU_ASSERT_EQUAL(nb, list_count((t_abstract_list *)get_shell_env()->history.list));

	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history after deleting entry 1:");
		print_history(get_shell_env()->history.list, 0);
	#endif

}

void	history_to_file()
{
	char	*av[][4] = {
						{"history", "-w", "test", NULL}, // should overwrite or create test
						{"history", "-a", "test", NULL}, // shoud do nothing
						{"history", "-a", NULL, NULL} // should append not already appended lines
					};

	builtin_history(3, av[0], NULL);
	CU_ASSERT_NOT_EQUAL(open("test", O_RDONLY), -1);

	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("This history should have been appended to %s once only \
					and added to %s:\n", HISTFILE, "test");
		print_history(get_shell_env()->history.list, 0);
	#endif

	builtin_history(3, av[1], NULL);
	builtin_history(2, av[2], NULL);
}

void	history_from_file()
{
	t_history *history;
	char *av[][4] = {
		{"history", "-r", NULL, NULL},
		{"history", "-r", "test", NULL},
		{"history", "-n", "test", NULL},
	};

	history = get_shell_env()->history.list;

	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history list before reading: ");
		print_history(history, 0);
	#endif

	builtin_history(2, av[0], NULL);

	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("State of history list after reading %s\n: ", HISTFILE);
		print_history(get_shell_env()->history.list, 0);
	#endif
	CU_ASSERT_PTR_NOT_NULL(get_shell_env()->history.list);
	history = get_shell_env()->history.list;
	builtin_history(3, av[1], NULL);
	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("State of history list after reading %s\n: ", "test");
		print_history(get_shell_env()->history.list, 0);
	#endif
	if (history)
		CU_ASSERT_PTR_NOT_NULL(history->next);
}

void	history_clear()
{
	char *av[] = {"history", "-c"};


	builtin_history(2, av, NULL);
	CU_ASSERT_PTR_NULL(get_shell_env()->history.list);
	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history after clearing all (should be empty!):");
		print_history(get_shell_env()->history.list, 0);
	#endif
}

void 	history_s_option()
{
	t_history *history;
	// t_history *new;
	char	*av[][6] = {
						{"history", "-s", "one", "two", "three", NULL},
						{"history", "-s", "-a", NULL}
					};
	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("State of history before -s: \n");
		print_history(get_shell_env()->history.list, 0);
	#endif

	builtin_history(5, av[0], NULL);
	history = get_shell_env()->history.list;

	while (history->next)
		history = history->next;
	CU_ASSERT_STRING_EQUAL(history->line, "one two three\n");

	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("State of history after -s: \n");
		print_history(get_shell_env()->history.list, 1);
	#endif

	builtin_history(3, av[1], NULL);
	// new = get_shell_env()->history;
	// list_goto_last((t_abstract_list **)&new);
	// CU_ASSERT_PTR_EQUAL(history, new);

	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("State of history after -s without args: \n");
		print_history(get_shell_env()->history.list, 0);
	#endif
}

void 	history_p_option()
{
	t_history *history;
	// t_history *new;
	char	*av[][6] = {
						{"history", "-p", "!!", "!2", NULL},
						{"history", "-p", NULL}
					};

	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("State of history before -p: \n");
		print_history(get_shell_env()->history.list, 0);
	#endif

	history = get_shell_env()->history.list;
	while (history->next)
		history = history->next;

	builtin_history(4, av[0], NULL);
	// new = get_shell_env()->history;
	// list_goto_last((t_abstract_list **)&new);
	// CU_ASSERT_PTR_EQUAL(history, new);

	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("State of history after -p (should be the same without last line): \n");
		print_history(get_shell_env()->history.list, 0);
	#endif

	/*
		builtin_history(2, av[1], NULL);
	 	CU_ASSERT_STRING_EQUAL(history->next->line, "history -p");
	 */
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

	builtin_history(2, av[0], NULL);
	// builtin_history(2, av[1], NULL);
	// builtin_history(3, av[2], NULL);
	builtin_history(3, av[3], NULL);
	builtin_history(3, av[4], NULL);
}
