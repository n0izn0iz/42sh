#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

// #include "history.h"
#include "history/history_def.h"
#include "history_substitutions.h"

static void		save_search(char *to_find)
{
	t_sh_history	*history;

	history = &get_shell_env()->history;
	if (history->last_search)
		ft_strdel(&history->last_search);
	history->last_search = ft_strdup(to_find);
}

static char		*hist_search(t_history *history, char *to_find, \
							bool must_start)
{
	// if find
	while (history)
	{
		if ((must_start && str_in_str(to_find, history->line, 0, true)) \
			|| (!must_start && str_in_str(to_find, history->line, 0, false)))
		{
			ft_strdel(&to_find);
			return (ft_strtrim(history->line));
		}
		history = history->prev;
	}
	ft_strdel(&to_find);
	return (NULL);
}

static bool		delimit_to_find(char *str, int *i, t_uint *end, bool must_start)
{
	bool	save;

	save = 0;
	if (must_start)
	{
		while (str[*i] && !start_word_designator(str[*i]) \
				&& !is_posix_blank(str[*i]) && str[*i] != '\n')
			(*i)++;
	}
	else
	{
		if (str[*i - 1] && (str[*i - 1] == '?'))
			save = 1;
		while (str[*i] && !is_posix_blank(str[*i]) \
				&& str[*i] != '\n' && str[*i] != '?')
			(*i)++;
		if (str[*i] && (str[*i] == '?'))
			(*end)++;
		(*end)++;
	}
	*end += *i;
	return (save);
}

char		*find_in_history(bool must_start, t_history *history, \
								char *str, t_uint *end)
{
	char	*to_find;
	int		i;
	bool	save;

	i = 0;
	list_goto_last((t_abstract_list **)&history);
	save = delimit_to_find(str, &i, end, must_start);
	to_find = ft_strsub(str, 0, i);
	if (save)
		save_search(to_find);
	return (hist_search(history, to_find, must_start));
}
