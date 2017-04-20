#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history_substitutions.h"
#include "string_substitution.h"

#include "history/builtin/history.h"

int			start_substitution(char **str, t_uint *start, char *hist_entry)
{
	t_uint	end;
	int		should_run;
	bool 	quote;

	should_run = 1;
	end = *start;
	if (!hist_entry)
	{
		if (!(hist_entry = get_history_entry(&(*str)[*start + 1], &end)))
			error_builtin(NULL, ft_strsub(*str, *start, end - *start), \
							EV_NOT_FOUND);
		if ((*str)[end])
			end++;
	}
	else
		end += 2;
	if ((*str)[end] && start_word_designator((*str)[end]))
		get_entry_word(&hist_entry, &(*str)[end], &end);
	if (end < ft_strlen(*str) && (*str)[end] == ':')
		should_run = apply_modifiers(&(*str)[end], &hist_entry, &end, &quote);
	if (get_error() == NO_ERROR)
	{
		if (quote)
			quote_word(&hist_entry);
		perform_substitution(str, hist_entry, start, end);
		return (should_run);
	}
	ft_strdel(&hist_entry);
	return (-1);
}

static bool	is_blank_equal_ret(char c)
{
	if (is_posix_blank(c) || c == '\n' || c == '=')
		return (1);
	return (0);
}

void		bang_sharp(char **str, t_uint *i, int *should_run)
{
	char *tmp;

	if (*i > 0)
		*should_run = start_substitution(str, i, ft_strsub(*str, 0, *i));
	else if (ft_strlen(*str) > 2)
	{
		tmp = ft_strsub(*str, 2, ft_strlen(*str) - 2);
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
	{
		ft_strdel(str);
		*str = ft_strdup("\n");
	}
}

static void	check_quotes(char *str, t_uint *i, bool *quoted)
{
	if (str[*i] == '\\')
		*i += 2;
	else if (str[*i] == '\'')
		*quoted = !(*quoted);
}

/*
**	'!' starts a substitution on a history entry
** 	or the line typed so far if the designator is '#'
**	'^' starts a quick substitution (^str1^str2[^])
**	should_run determines if the command is executed or not
**	(it isn't with the p modifier or in case of an error,
**	 but the p modifier still saves it to the history list
*/

int			history_substitution(char **str)
{
	t_uint		i;
	bool		quoted;
	int			should_run;

	i = 0;
	quoted = 0;
	should_run = 1;
	set_error(NO_ERROR);
	while (i < ft_strlen(*str))
	{
		if (get_error() != NO_ERROR)
			return (-1);
		check_quotes(*str, &i, &quoted);
		if (is_bang((*str)[i]) && !quoted)
		{
			if ((*str)[i + 1] && (*str)[i + 1] == '#')
				bang_sharp(str, &i, &should_run);
			else if (!is_blank_equal_ret((*str)[i + 1]))
				should_run = start_substitution(str, &i, NULL);
		}
		else if (is_circumflex((*str)[i]))
			quick_substitution(str, &i);
		if (i < ft_strlen(*str))
			i++;
	}
	if (!should_run)
		add_to_history_list(&get_shell_env()->history.list, create_history_entry(*str));
	return (should_run);
}
