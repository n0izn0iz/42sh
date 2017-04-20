#include "history.h"
#include "errors.h"
#include "abstract_list.h"

void		print_history(t_history *history, int start)
{
	int		i;

	i = 1;
	while (history)
	{
		if (i > start)
		{
			ft_putnbr(i);
			ft_putstr("  "); // alignment // most digits
			ft_putstr(history->line);
		}
		i++;
		history = history->next;
	}
}

void		print_history_n(bool more_args, char *n, t_history *history)
{
	if (more_args)
		error_builtin("history", NULL, TOO_MANY_ARGS);
	else
		print_history(history, list_count((t_abstract_list *)history) - ft_atoi(n));
}