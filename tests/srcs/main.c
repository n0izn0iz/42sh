#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#include <CUnit/Console.h>
#include <libft.h>
#include "test_utils.h"
#include "ftsh.h"

static void print_error(void)
{
	if (CU_get_error() != CUE_SUCCESS)
		printf("Error: %s\n",CU_get_error_msg());
}

static int init_ftsh(void) {
	char *ftsh_argv[] = {
		"42sh",
		NULL
	};
	init(1, ftsh_argv);
	return (0);
}

int main(int argc, char **argv)
{
	CU_ErrorCode	result;

	// Declare
	CU_TestInfo		binary_tests[] = {
	  { "Check that an empty command string returns no error", empty_command_string },
	  { "Check that an unclosed single quote returns an error", unclosed_quote },
	  { "Check that an unclosed double quote returns an error", unclosed_double_quote },
	  CU_TEST_INFO_NULL
	};
	CU_TestInfo		tokenizer_tests[] = {
		{ "Check that io numbers are lexed", construct_io_number_token },
	  	{ "Check that construct_token copies the string", construct_token_copy_string },
	  CU_TEST_INFO_NULL
	};
	CU_TestInfo		init_tests[] = {
		{ "Check that init() sets the error ptr and exits without error", init_sets_error_ptr },
		CU_TEST_INFO_NULL
	};
	// CU_TestInfo		history_tests[] = {
	// 	{ "Print last 3 history\n", history_print_offset},
	// 	{ "Add one element to history",	history_add_one},
	// 	{ "Delete one specific entry", history_delete},
	// 	{ "History to file\n", history_to_file},
	// 	{ "Print history\n", history_print},
	// 	{ "Clear history", history_clear},
	// 	{ "History reinitialization", initialize_history },
	// 	{ "History error handling", history_errors },
	// 	{ "Read history from file", history_from_file},
	// 	{ "History s option appends args to history list as one entry + doesn't save", history_s_option},
	// 	{ "History p option displays args with substitution + doesn't save", history_p_option},
	//   CU_TEST_INFO_NULL
	// };
	CU_TestInfo		bang_tests[] = {
		{ "Double bang returns last entry", bang_bang },
		{ "!n returns nth entry, !-n returns (last - n)th entry", bang_n },
		{ "Most recent entry starting with str (\"!str\"), or containing str (\"!?str[?\\n]\")", bang_search },
		{ "Word selection", bang_word_selection },
		{ "Typed line selection + quoting", bang_sharp_quotes},
		{ "Substitution modifiers", bang_modifiers},
		{ "Misc bang errors return -1", bang_errors },
	  CU_TEST_INFO_NULL
	};
	CU_TestInfo		builtins_tests[] = {
		{ "Check that save_the_day does it's job", cd_save_the_day },
		CU_TEST_INFO_NULL
	};

	CU_SuiteInfo	suites[] = {
		{ "Init", NULL, NULL, NULL, NULL, init_tests },
		{ "Tokenizer", NULL, NULL, NULL, NULL, tokenizer_tests },
		{ "Bang", init_ftsh, NULL, NULL, NULL, bang_tests },
		// { "History", NULL, NULL, NULL, NULL, history_tests },
		{ "Builtins", NULL, NULL, NULL, NULL, builtins_tests },
		{ "Binary", NULL, NULL, NULL, NULL, binary_tests },
		CU_SUITE_INFO_NULL
	};

	// Init
	CU_initialize_registry();
	print_error();

	// Register
	CU_register_suites(suites);
	print_error();

	// Run
	if (argc > 1 && ft_strequ(argv[1], "-i"))
		CU_console_run_tests();
	else
	{
		CU_basic_set_mode(CU_BRM_VERBOSE);
		print_error();
		CU_basic_run_tests();
	}
	print_error();

	// Get result
	if (CU_get_number_of_failures() > 0)
		result = EXIT_FAILURE;
	else
		result = EXIT_SUCCESS;
	print_error();

	// Clean
	CU_cleanup_registry();
	print_error();

	return (result);
}
