# include <stdbool.h>
# include <libft.h>
# include "utils.h"

bool is_an_argument(char **argv, int pos)
{
	if (ft_tablen(argv) <= pos)
		return (false);
	if (!ft_strcmp(ARG_STOP, argv[pos]))
		return (false);
	return (!is_an_option(argv, pos));
}
