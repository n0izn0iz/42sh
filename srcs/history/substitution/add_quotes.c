#include "utils.h"
#include "history_substitutions.h"
#include "string_substitution.h"

static void		add_quoted_backslash(char **word, size_t first)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strsub(*word, 0, first);
	tmp2 = ft_strjoin(tmp, "'\\'");
	ft_strdel(&tmp);
	tmp3 = ft_strdup(&(*word)[first]);
	tmp = ft_strjoin(tmp2, tmp3);
	ft_strdel(word);
	ft_strdel(&tmp2);
	ft_strdel(&tmp3);
	*word = ft_strdup(tmp);
	ft_strdel(&tmp);
}

/*
**	adds simple-quoted backslashes to quote simple quotes
*/

static void		quote_quotes(char **word)
{
	int		len;
	char	*tmp;
	int		i;

	i  = -3;
	len = ft_strlen(*word);
	while (i < (int)ft_strlen(*word))
	{
		if (!(tmp = ft_strchr(*word + i + 3, '\'')))
			break ;
		i = tmp - *word + 1;
		add_quoted_backslash(word, tmp - *word);
	}
}

/*
**	simple-quotes word
*/

void			quote_word(char **word)
{
	char	*tmp;

	quote_quotes(word);
	tmp = ft_strjoin("\'", *word);
	ft_strdel(word);
	*word = ft_strjoin(tmp, "\'");
	ft_strdel(&tmp);
}

static void		add_quote_at_pos(t_string **l_str, size_t pos)
{
	t_string	*new;

	new = memalloc_or_die(sizeof(t_string));
	new->c = '\'';
	new->next = NULL;
	list_push_at_pos(pos, (t_abstract_list **)l_str, (t_abstract_list *)new);
}

/*
** quotes each word delimited by space, tab or \n
*/

void			quote_per_word(char **str)
{
	t_string	*l_str;
	t_string	*beg;
	int			pos;

	pos = 0;
	quote_word(str);
	l_str = str_to_list(*str);
	beg = l_str;
	while (l_str)
	{
		if (is_posix_blank(l_str->c) || l_str->c == '\n')
		{
			add_quote_at_pos(&beg, pos);
			pos++;
			while (is_posix_blank(l_str->c) || l_str->c == '\n')
			{
				l_str = l_str->next;
				pos++;
			}
			add_quote_at_pos(&beg, pos);
			pos++;
		}
		l_str = l_str->next;
		pos++;
	}
	ft_strdel(str);
	*str = get_string_from_list(beg);
	free_string(beg);
}
