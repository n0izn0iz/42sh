#include "event_callback_def.h"
#include "abstract_list.h"
#include <libft.h>

EV_CB_RET	ev_newline(t_editor *ed)
{
	ev_cursor_end(ed);
	close_history(ed);
	add_to_string(ed, '\n');
	refresh_line(ed);
}

EV_CB_RET	ev_cancel(t_editor *ed)
{
	(void)ed;
}

EV_CB_RET	ev_exit(t_editor *ed)
{
	if (ed->string_size == 0)
	{
		write(STDOUT_FILENO, "\x0A", 1);
		builtin_exit(0, NULL);
	}
}

EV_CB_RET	ev_delete(t_editor *ed)
{
	void **p;

	if (ed->cursor_position <= 0)
		return ;
	ed->need_refresh = true;
	ev_cursor_left(ed);
	p = list_pop_at_pos(ed->cursor_position, (t_abstract_list **)&ed->string);
	free(p);
}

EV_CB_RET	ev_delete_right(t_editor *ed)
{
	void **p;

	ed->need_refresh = true;
	p = list_pop_at_pos(ed->cursor_position, (t_abstract_list **)&ed->string);
	free(p);
}
