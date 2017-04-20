#include "test_utils.h"
#include <libft.h>

#include "shell_env.h"
#include "history/substitution/history_substitutions.h"
#include "ftsh.h"
#include "utils.h"


#define NB_SUB_TESTS 41
#define NB_ERR_TESTS 11

#define BANG_TEST_VERBOSE

/*
	to test your own strings:
	- add the string in get_bang_tests
	- add the expected result at the same index in get_bang_results
	- change the NB_SUB_TEST define
	- optionnally modify the history_test_file but remember it changes all the results!
		(history is printed out at the beginning of test suite)
	- copy one of the bang_ functions (not the error one), change value and condition of i
	- add its prototype to history.h of course!
*/

static char	**get_bang_tests()
{
	int i;
	static char **malloced_tests;
	char *tests[] = {
		"!!",
		"!!!!",
		"echo !1",
		"!2",
		"!-2",
		"!-6",
		"!fi grj",
		"echo !?ou",
		"!t",
		"!?ne?:0",
		"!!:0-2",
		"!!:-2sijf",
		"!!:2-",
		"!!:1-3",
		"!!:1-*",
		"!!:2*",
		"!!:^",
		"!!*",
		"!!$",
		"!$",
		"!!^",
		"!!-",
		"!!-2",
		"!!:*",
		"!!:$",
		"!*",
		"!^",
		"un deux \"!#",
		"!#",
		"!#test",
		"\\!#",
		"test '!4'",
		"test '!#cocou' !2",
		"bli bla \"!#:2",
		"bli bla \"test !#:2",
		"!!:s/un/test\n",
		"!!:gsptrptestp",
		"^un^test\n",
		"^un^test^\n",
		"!!:s/un/\\/slash\n",
		"!!:x"};// !!%"

	i = 0;
	malloced_tests = malloc(sizeof(char *) * (NB_SUB_TESTS + 1));
	while (i < NB_SUB_TESTS)
	{
		malloced_tests[i] = ft_strdup(tests[i]);
		i++;
	}
	malloced_tests[i] = NULL;
	return (malloced_tests);
}

static char **get_bang_results()
{
	static char *results[] = {
		"un deux trois quatre cinq",
		"un deux trois quatre cinqun deux trois quatre cinq",
		"echo one",
		"two",
		"five",
		"one",
		"five grj",
		"echo four",
		"three",
		"one",
		"un deux trois",
		"un deux troissijf",
		"trois quatre",
		"deux trois quatre",
		"deux trois quatre*",
		"trois quatre cinq",
		"deux",
		"deux trois quatre cinq",
		"cinq",
		"cinq",
		"deux",
		"un deux trois quatre",
		"un deux trois",
		"deux trois quatre cinq",
		"cinq",
		"deux trois quatre cinq",
		"deux",
		"un deux \"un deux \"",
		"\n",
		"test",
		"\\!#",
		"test '!4'",
		"test '!#cocou' two",
		"bli bla \"\"",
		"bli bla \"test \"test",
		"test deux trois quatre cinq\n",
		"un deux testois quateste cinq",
		"test deux trois quatre cinq\n",
		"test deux trois quatre cinq\n",
		"/slash deux trois quatre cinq\n",
		"\'un\' \'deux\' \'trois\' \'quatre\' \'cinq\'"};
	return (results);
}

static char	**get_bang_error_tests()
{
	static char *error_tests[] = {
		"echo !0\n",
		"!-\n",
		"!-0",
		"!6534",
		"!!:40",
		"test !45",
		"^flkjf\n",
		"^dg^fe\n",
		"!?ju",
		"!!:s/gjgf ehco\n",
		"!!:s/dg/rf/ jg"
	};
	return (error_tests);
}

void	bang_bang()
{
	char **tests;
	char **results;
	int i;

	i = 0;
	tests = get_bang_tests();
	results = get_bang_results();
	while (i <= 2)
	{
		#ifdef BANG_TEST_VERBOSE
		ft_printf("\nstr: \"%s\", expected: \"%s\"", tests[i], results[i]);
		#endif

		history_substitution(&tests[i]);

		#ifdef BANG_TEST_VERBOSE
		ft_printf(", result: \"%s\"", tests[i]);
		#endif

		CU_ASSERT_STRING_EQUAL(tests[i], results[i]);
		i++;
	}
	ft_freetabchar(tests);
}

void	bang_n()
{
	char **tests;
	char **results;
	int i;

	i = 2;
	tests = get_bang_tests();
	results = get_bang_results();
	while (i <= 5)
	{
		#ifdef BANG_TEST_VERBOSE
		ft_printf("\nstr: \"%s\", expected: \"%s\"", tests[i], results[i]);
		#endif

		history_substitution(&tests[i]);

		#ifdef BANG_TEST_VERBOSE
		ft_printf(", result: \"%s\"", tests[i]);
		#endif

		CU_ASSERT_STRING_EQUAL(tests[i], results[i]);
		i++;
	}
	ft_freetabchar(tests);
}

void	bang_search()
{
	char **tests;
	char **results;
	int i;

	i = 7;
	tests = get_bang_tests();
	results = get_bang_results();
	while (i < 10)
	{
		#ifdef BANG_TEST_VERBOSE
		ft_printf("\nstr: \"%s\", expected: \"%s\"", tests[i], results[i]);
		#endif

		history_substitution(&tests[i]);

		#ifdef BANG_TEST_VERBOSE
		ft_printf(", result: \"%s\"", tests[i]);
		#endif

		CU_ASSERT_STRING_EQUAL(tests[i], results[i]);
		i++;
	}
	ft_freetabchar(tests);
}

void	bang_word_selection()
{
	char **tests;
	char **results;
	int i;

	i = 10;
	tests = get_bang_tests();
	results = get_bang_results();
	while (i < 27)
	{
		#ifdef BANG_TEST_VERBOSE
			ft_printf("\nstr: \"%s\", expected: \"%s\"", tests[i], results[i]);
		#endif

		history_substitution(&tests[i]);

		#ifdef BANG_TEST_VERBOSE
			ft_printf(", result: \"%s\"", tests[i]);
		#endif

		CU_ASSERT_STRING_EQUAL(tests[i], results[i]);
		i++;
	}
	ft_freetabchar(tests);
}

void	bang_sharp_quotes()
{
	char **tests;
	char **results;
	int i;

	i = 27;
	tests = get_bang_tests();
	results = get_bang_results();
	while (i < 36)
	{
		#ifdef BANG_TEST_VERBOSE
			ft_printf("\nstr: \"%s\", expected: \"%s\"", tests[i], results[i]);
		#endif

		history_substitution(&tests[i]);

		#ifdef BANG_TEST_VERBOSE
			ft_printf(", result: \"%s\"\n", tests[i]);
		#endif

		if (i != 34)
			CU_ASSERT_STRING_EQUAL(tests[i], results[i]);
		i++;
	}
	ft_freetabchar(tests);
}

void	bang_modifiers()
{
	char	**tests;
	char 	**results;
	int		i;

	i = 36;
	tests = get_bang_tests();
	results = get_bang_results();
	while (i < NB_SUB_TESTS)
	{
		#ifdef BANG_TEST_VERBOSE
			ft_printf("\nstr: \"%s\", expected: \"%s\"", tests[i], results[i]);
		#endif

		history_substitution(&tests[i]);

		#ifdef BANG_TEST_VERBOSE
			ft_printf(", result: \"%s\"", tests[i]);
		#endif

		CU_ASSERT_STRING_EQUAL(tests[i], results[i]);
		i++;
	}
	ft_freetabchar(tests);
}

void	bang_errors()
{
	char **tests;
	int i;

	i = 0;
	tests = get_bang_error_tests();
	while (i < NB_ERR_TESTS)
	{
		#ifdef BANG_TEST_VERBOSE
		ft_printf("\nstr: \"%s\"", tests[i]);
		#endif

		CU_ASSERT_EQUAL(history_substitution(&tests[i]), -1);
		i++;
	}
}
