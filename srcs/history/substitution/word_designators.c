
#include "utils.h"
#include "range.h"

#include "break_input/tokenizer.h"
#include "history_substitutions.h"

bool			start_word_designator(char c)
{
	if (c == ':' || c == '^' || c == '%' || c == '*' || c == '-' || c == '$')
		return (true);
	return (false);
}

static char		*get_last_word(char *line)
{
	t_token *words;
	t_token *tmp;
	char 	*word;

	word = NULL;
	if ((words = tokenize_for_substitution(line)))
	{
		tmp = words;
		while (tmp->next)
			tmp = tmp->next;
		word = ft_strdup(tmp->str);
		delete_all_tokens(&words);
	}
	return (word);
}

static void		match_last_search(char **hist_entry, char **result)
{
	t_token *words;
	t_token	*tmp;
	char	*to_find;

	if ((to_find = get_shell_env()->history.last_search))
	{
		if ((words = tokenize_for_substitution(*hist_entry)))
		{
			tmp = words;
			while (tmp)
			{
				if (str_in_str(to_find, tmp->str, 0, false))
				{
					*result = ft_strdup(tmp->str);
					delete_all_tokens(&words);
					return ;
				}
				tmp = tmp->next;
			}
		}
	}
	else
		*result = ft_strnew(1);
}

/*
**	'*' = range 1-last (all arguments)
**	'^' word 1 (first argument)
**	'$' last word
**	'%' word that matches last ?str[?] search
**	'[n]-[m]' a range of words
*/

void			parse_word_designators(char *str, int *i, t_range *range, \
										char **entry, char **result)
{
	/*
		!!!!!
		It is not an error to use ‘*’ if there is just one word in the event;
		the empty string is returned in that case.
	*/
	if (str[*i] == '*')
	{
		range->start = 1;
		range->end = -1;
		range->empty_ok = true;
	}
	else if (str[*i] == '^')
		range->start = range->end = 1;
	else if (str[*i] == '$')
	{
		*result = get_last_word(*entry);
		ft_strdel(entry);
		*entry = ft_strdup(*result);
		ft_strdel(result);
	}
	else if (str[*i] == '%')
		match_last_search(entry, result);
	else if (str[*i] == '-')
		parse_range(str, i, range);
	(*i)++;
}