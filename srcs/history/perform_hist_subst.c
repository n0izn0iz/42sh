#include "libft.h"
#include "utils.h"
// #include "errors.h"

#include "history_substitutions.h"

void		perform_substitution(char **str, char *hist_entry, \
								t_uint *start, t_uint end)
{
	char		*to_sub;

	to_sub = ft_strsub(*str, *start, end - *start);
	find_and_replace(str, to_sub, hist_entry, *start);
	*start = end;
	ft_strdel(&hist_entry);
	ft_strdel(&to_sub);
	ft_putstr(*str);
}

void 		quick_substitution(char **str, t_uint *start)
{
	char		*hist_entry;
	t_uint		end;

	end = *start;
	hist_entry = get_nth_entry(get_shell_env()->history.list, -1);
	substitute_str(&(*str)[end], &hist_entry, &end, false);
	if (get_error() != NO_ERROR)
		return ;
	perform_substitution(str, hist_entry, start, end);
}