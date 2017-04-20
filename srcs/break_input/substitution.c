#include <stdbool.h>
#include <libft.h>
#include "errors.h"
#include "shell_env.h"

bool		is_substitution_start(char const *s)
{
	// does the tokenizer take into account the quoting for start? (it does for end - below)
	if (s && *s && *s == '`')
		return (true);
	return (false);
}

char const	*find_substitution_end(char const *str)
{
	set_error(NO_ERROR);
	while (*str)
	{
		/* <backslash> shall retain its literal meaning, except when
			followed by: '$', '`', or <backslash> */
		if (*str == '\\' && (*(str + 1) == '`' || *(str + 1) == '\\'))
			str++;
		else if (*str == '`')
			return (str);
		str++;
	}
	set_error(UNMATCHED_BACKQUOTE);
	get_shell_env()->last_unmatched = UNMATCHED_BACKQUOTE;
	return (NULL);
}
