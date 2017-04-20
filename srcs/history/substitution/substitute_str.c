#include "string_substitution.h"

static void	save_substitution(t_str_subst subst)
{
	t_sh_history	*history;

	history = &get_shell_env()->history;
	if (history->last_subst.to_find)
	{
		ft_strdel(&history->last_subst.to_find);
		ft_strdel(&history->last_subst.replace);
	}
	history->last_subst = subst;
}

void		replace_and_repeat(t_str_subst *subst, char **str)
{
	t_uint 		start;

	start = 0;
	if (subst->repeat)
	{
		while (start < ft_strlen(*str))
			start = find_and_replace(str, subst->to_find, subst->replace, start);
	}
	else
	{
		if (!subst->to_find || find_and_replace(str, subst->to_find, subst->replace, 0) < 0)
			set_error(SUBST_FAIL);
	}
}

/*
**	replaces all unquoted '&' in subst.replace (new) by subst.to_find (old)
*/

static void	replace_and_by_old(t_str_subst *subst)
{
	t_str_subst	subst_and;
	char		*tmp;
	int			i;

	i = 0;
	while ((tmp = ft_strchr(&subst->replace[i], '&')))
	{
		if (tmp[i - 1] != '\\')
		{
			subst_and.to_find = "&";
			subst_and.replace = subst->to_find;
			subst_and.repeat = false;
			replace_and_repeat(&subst_and, &subst->replace);
		}
		i = tmp - subst->replace + 1;
	}
	take_out_backslashes(&subst->replace, '&');
}

void		substitute_str(char *modifier, char **str, t_uint *i, bool repeat)
{
	t_str_subst	subst;
	char		delimiter;
	t_error_id	err;

	subst.repeat = repeat;
	delimiter = modifier[(*i)++];
	// // + handle quoted
	if (!(subst.to_find = get_delimited_str(&modifier[*i], delimiter, i)))
		return ;
	(*i)++;
	subst.replace = get_delimited_str(&modifier[*i], delimiter, i);
	replace_and_by_old(&subst);
	if (modifier[*i] == delimiter && modifier[*i - 1] != delimiter)
		(*i)++;
	replace_and_repeat(&subst, str);
	save_substitution(subst);
	if ((err = get_error()) != NO_ERROR)
	{
		modifier = ft_strsub(modifier, 0, *i);
		error_builtin(modifier, NULL, err);
		ft_strdel(&modifier);
	}
}

void		substitute_words_str(char *modifiers, char **str, t_uint *i)
{
	t_token 	*words;
	t_token 	*tmp;

	words = tokenize_for_substitution(*str);
	tmp = words;
	ft_strdel(str);
	while (words)
	{
		substitute_str(modifiers, &words->str, i, false);
		str_join_with_space(str, words->str);
		words = words->next;
	}
	delete_all_tokens(&tmp);
}
