#include "builtins.h"
#include "../../parse_input/syntax_tree.h"
#include "utils.h"
#include <libft.h>

BUILTIN_RET 		builtin_exit(BUILTIN_ARGS)
{
	(void)cmd;
	t_uchar	ret;

	if (argc > 1)
		ret = ft_atoi(argv[1]);
	else
		ret = get_last_exit_status();
	exit(ret);
}
