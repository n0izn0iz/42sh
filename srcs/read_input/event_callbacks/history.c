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
	while (*str)
	{
		add_to_string(ed, *str);
		str++;
	}
}

/***************************************/

EV_CB_RET 	event_history_up(EV_CB_ARGS)
{
	if (ed->history)
	{
		ed->need_refresh = true;
		list_free((t_abstract_list **)&ed->string);
		str_to_list(ed, ed->history->line);
		if (ed->history->prev)
			ed->history = ed->history->prev;
	}
}

EV_CB_RET 	event_history_down(EV_CB_ARGS)
{
	ed->need_refresh = true;
	list_free((t_abstract_list **)&ed->string);
	if (ed->history && ed->history->next)
	{
		ed->history = ed->history->next;
		str_to_list(ed, ed->history->line);
	}
}
