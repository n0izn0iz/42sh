#include "event_callback_def.h"
#include "history.h"
#include "abstract_list.h"
#include <libft.h>

/** general functions that can be moved/reused  **/

void	list_free(t_abstract_list **list)
{
	if ((*list) && (*list)->next)
		list_free(&(*list)->next);
	free(*list);
	*list = NULL;
}

void	str_to_list(t_editor *ed, char *str)
{
	if (str == NULL)
		return;
	while (*str)
	{
		add_to_string(ed, *str);
		str++;
	}
}

/***************************************/

EV_CB_RET 	event_history_up(EV_CB_ARGS)
{
	char	*trimed;

	if (ed->history)
	{
		clear_line(ed);
		list_free((t_abstract_list **)&ed->string);
		trimed = ft_strtrim(ed->history->line);
		str_to_list(ed, trimed);
		free(trimed);
		if (ed->history->prev)
			ed->history = ed->history->prev;
		put_line(ed);
	}
}

EV_CB_RET 	event_history_down(EV_CB_ARGS)
{
	char	*trimed;

	list_free((t_abstract_list **)&ed->string);
	clear_line(ed);
	if (ed->history && ed->history->next)
	{
		ed->history = ed->history->next;
		trimed = ft_strtrim(ed->history->line);
		str_to_list(ed, trimed);
		free(trimed);
	}
	put_line(ed);
}
