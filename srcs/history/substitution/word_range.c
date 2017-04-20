#include "abstract_list.h"
#include "utils.h"
#include "range.h"

#include "history_substitutions.h"

int 		parse_range(char *str, int *i, t_range *range)
{
	// ‘-y’ abbreviates ‘0-y’
	if (str[*i] == '-')
	{
		range->start = 0;
		if (ft_isdigit(str[(*i) + 1]))
		{
			range->end = ft_atoi(&str[*i + 1]);
			*i += number_len(&str[*i + 1]) + 1;
		}
		else
			range->end = -2;
	}
	else
	{
		range->start = ft_atoi(&str[*i]);
		*i += number_len(&str[*i]);
		if (str[*i] && str[*i] == '-')
		{
			(*i)++;
			if (str[*i] && ft_isdigit(str[*i]))
			{
				range->end = ft_atoi(&str[*i]);
				*i += number_len(&str[*i]);
			}
			//'x-$' = x-last
			else if (str[*i] && str[*i] == '$')
			{
				(*i)++;
				range->end = -1;
			}
			// x- is x-$ but omits the last word
			else
				range->end = -2;
		}
		// x*  = x-$
		else if (str[*i] == '*')
		{
			(*i)++;
			range->end = -2;
		}
	}
	return (0);
}

void 		range_selection(char *str, int *i, t_range *range, char **words)
{
	//  x-y ; x- ; -y  A range of words
	if (ft_strchr(str, '-'))
	{
		if (parse_range(str, i, range) < 0)
		{
			*words = ft_strnew(1);
			return ;
		}
	}

	// designator = n => nth word ; n* = n-$
	else
	{
		range->start = ft_atoi(&str[*i]);
		if (str[*i + number_len(&str[*i])] && str[*i + number_len(&str[*i])] == '*')
		{
			*i += number_len(&str[*i]) + 1;
			range->end = -1;
		}
		else
			range->end = range->start;
		*i += number_len(&str[*i]);
	}
}

static char		*word_range_collapse(t_token *words, t_uint nb_wds, bool empty_ok)
{
	char	*word_range;

	word_range = ft_strdup(words->str);
	while (nb_wds > 0)
	{
		words = words->next;
		if (!words)
		{
			if (empty_ok)
				return (ft_strnew(1));
			ft_strdel(&word_range);
			return (NULL);
		}
		str_join_with_space(&word_range, words->str);
		nb_wds--;

	}
	return (word_range);
}

char			*get_word_range(char *line, t_range *range)
{
	t_token *words;
	t_uint	nb_wds;
	char 	*str;
	t_token	*tmp;

	str = NULL;
	if ((words = tokenize_for_substitution(line)))
	{
		tmp  = words;
		if (range->end < 0)
			range->end += list_count((t_abstract_list *)words);
		nb_wds = range->end - range->start;
		if (!list_goto_n((t_abstract_list **)&words, range->start))
		{
			delete_all_tokens(&tmp);
			return (NULL);
		}
		str = word_range_collapse(words, nb_wds, range->empty_ok);
		delete_all_tokens(&tmp);
	}
	return (str);
}