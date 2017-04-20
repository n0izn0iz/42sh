#include "expansion.h"
#include "strlist.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>
#include "range.h"
#include "utils.h"
#include "abstract_list.h"
#include "break_input/quoting.h"

static void		end_of_quote(char const *word, t_range *delimit)
{
	char 	quote;

	quote = *word;
	delimit->end++;
	while (word[delimit->end] != quote)
		delimit->end++;
}

static void		skip_posix_blanks(char const *word, int *i)
{
	while (word[*i] && (is_posix_blank(word[*i]) || word[*i] == '\n'))
		(*i)++;
}

static void		add_field(char const *word, t_strlist **result, t_range *delimit)
{
	char		*tmp;

	tmp = ft_strsub(word, delimit->start, delimit->end - delimit->start);
	#ifdef EXPANSION_DEBUG
		ft_dprintf(2, "Adding field, str: %s\n", tmp);
	#endif
	strlist_append(result, tmp);
	// Each occurrence in the input of an IFS character that is not IFS white space,
	// along with any adjacent IFS white space, shall delimit a field, as described previously.
	// Non-zero-length IFS white space shall delimit a field
	skip_posix_blanks(word, &delimit->end);
	delimit->start = delimit->end;
	ft_strdel(&tmp);
}

/*
**	scan the results of expansions and substitutions
** 	that did not occur in double-quotes and split into fields
*/

// TO DO: white space fields (see comment above)

t_strlist *field_splitting(char const *word)
{
	t_strlist	*result;
	t_range		delimit;

	ft_bzero(&delimit, sizeof(t_range));
	while (word[delimit.start])
	{
		while (word[delimit.end] && !is_posix_blank(word[delimit.end]) \
				&& word[delimit.end] != '\n')
		{
			if (is_quote(word[delimit.end]))
				end_of_quote(&word[delimit.end], &delimit);
			delimit.end++;
		}
		add_field(word, &result, &delimit);
	}
	return (result);
}
