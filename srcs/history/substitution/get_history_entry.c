#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history/history_def.h"
#include "history_substitutions.h"

char			*get_nth_entry(t_history *history, int n)
{
	if (n == 0 || !history)
		return (NULL);
	else if (n < 0)
	{
		list_goto_last((t_abstract_list **)&history);
		while (n < -1)
		{
			if (!(history = history->prev))
				return (NULL);
			n++;
		}
	}
	else
	{
		while (n > 1)
		{
			if (!(history = history->next))
				return (NULL);
			n--;
		}
	}
	return (ft_strtrim(history->line));
}

/*
** 		retrieves history entry according to what follows the first '!' :
**
**		- '!' or word designator
**		(':', ‘^’, ‘$’, ‘*’, ‘-’, or ‘%’)  => previous command
**		- n => entry at line n
**		- -n => entry n lines back
**		- ?str[?] => most recent command containing str
**		- str => most recent command that starts with str
**		- % =>
*/

char			*get_history_entry(char *designator, t_uint *end)
{
	t_history	*history;
	int			n;

	history = get_shell_env()->history.list;
	if (is_bang(*designator) || (start_word_designator(*designator) \
									&& *designator != '-'))
	{
		if (is_bang(*designator))
			(*end)++;
		return (get_nth_entry(history, -1));
	}
	else if (ft_isdigit(*designator) || *designator == '-')
	{
		n = ft_atoi(designator);
		*end += number_len(designator);
		return (get_nth_entry(history, n));
	}
	else if (*designator == '?')
		return (find_in_history(false, history, ++designator, end));
	/*
	!!! + store string search in shell_env !!! for :%
	*/
	else
		return (find_in_history(true, history, designator, end));
	return (NULL);
}
