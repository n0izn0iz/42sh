#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "history_substitutions.h"
#include "string_substitution.h"

/*
**	h removes the trailing pathname (/pathname)
**	t keeps only the trailing pathname
**	r removes a trailing suffix (.suffix)
**	e removes all but the trailing suffix
*/

static int	trimming_modifiers(char modifier, char **str)
{
	if (modifier == 'h')
	{
		remove_tail(str, '/');
		return (1);
	}
	else if (modifier == 't')
	{
		remove_head(str, '/');
		return (1);
	}
	else if (modifier == 'r')
	{
		remove_tail(str, '.');
		return (1);
	}
	else if (modifier == 'e')
	{
		remove_head(str, '.');
		return (1);
	}
	return (0);
}

static int	subst_modifiers(char modifier, char *modifiers, t_uint *i, \
							char **str)
{
	if (modifier == 's')
	{
		substitute_str(modifiers, str, i, false);
		return (1);
	}
	else if (modifier == '&')
	{
		replace_and_repeat(&get_shell_env()->history.last_subst, str);
		if (get_error() != NO_ERROR)
			print_name_and_error(get_error());
		return (1);
	}
	else if (modifier == 'g' && modifiers[*i] == 's')
	{
		(*i)++;
		substitute_str(modifiers, str, i, true);
		return (1);
	}
	else if (modifier == 'G' && modifiers[*i] == 's')
	{
		(*i)++;
		substitute_words_str(modifiers, str, i);
		return (1);
	}
	return (0);
}

/*
**	p prints the substituted command without executing it
**	q quotes the substituted string
**	x breaks the substituted string into words at \n sp \t
**		then quotes them
**	s/old/new[/] Substitutes new for the first occurrence of old
**				 in the event line.
**				 Any delimiter may be used in place of ‘/’.
**				 Final delimiter is optional if last character
**				 on the input line.
**				 If '&' appears in new, it is replaced by old
**				 A single backslash quotes the delimiter and '&'
**	[gG]s/old/new apply substitution to whole string (g) or once each word (G)
**	& repeats previous substitution
*/

static bool	pqx_mods(char modifier, char **str, bool *should_run, bool *quote)
{
	if (modifier == 'p')
	{
		*should_run = 0;
		return (true);
	}
	else if (modifier == 'q')
	{
		*quote = 1;
		return (true);
	}
	else if (modifier == 'x')
	{
		quote_per_word(str);
		return (true);
	}
	return (false);
}

static void	norm_init(bool *should_run, t_uint *i)
{
	*i = 0;
	*should_run = 1;
}

bool		apply_modifiers(char *modifiers, char **str, t_uint *end, \
							bool *quote)
{
	t_uint		i;
	bool		should_run;
	char		modifier;

	norm_init(&should_run, &i);
	while (modifiers[i])
	{
		if (modifiers[i] == ':')
		{
			modifier = modifiers[++i];
			i++;
			if (trimming_modifiers(modifier, str))
				continue ;
			else if (pqx_mods(modifier, str, &should_run, quote))
				continue ;
			else if (subst_modifiers(modifier, modifiers, &i, str))
				continue ;
			else
				return (should_run);
		}
		else
			break ;
	}
	(*end) += i;
	return (should_run);
}
