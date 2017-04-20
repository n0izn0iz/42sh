#include "shell_env.h"
#include "history.h"
#include "errors.h"
#include "utils.h"
#include "abstract_list.h"

static void	free_history(t_history **history)
{
	ft_strdel(&(*history)->line);
	free(*history);
	*history = NULL;
}

void		delete_entry_at(t_history **history, int offset)
{
	t_history	*tmp;

	tmp = *history;
	while (offset > 1)
	{
		tmp = tmp->next;
		offset--;
	}
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		*history = tmp->next;
	free_history(&tmp);
}

void		delete_history_entry(t_history **history, char *offset)
{
	int		n_offset;

	if (offset && str_is_digits(offset))
	{
		n_offset = ft_atoi(offset);
		if (n_offset <= 0 || \
			(size_t)n_offset > list_count((t_abstract_list *)*history))
			error_builtin("history", ft_strdup(offset), OUT_OF_RANGE);
		else
			delete_entry_at(history, n_offset);
	}
	else
		error_builtin("history", ft_strdup(offset), OUT_OF_RANGE);
}

void		clear_history_list(t_history **history)
{
	if (*history)
	{
		if ((*history)->next)
			clear_history_list(&(*history)->next);
		free_history(history);
	}
}
