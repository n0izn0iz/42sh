#include "event_callback_def.h"
#include <libft.h>

EV_CB_RET 	event_cursor_home(EV_CB_ARGS)
{
	while (ed->cursor_position > 0)
	{
		event_cursor_left(ed);
	}
}

EV_CB_RET 	event_cursor_end(EV_CB_ARGS)
{
	while (ed->string_size > ed->cursor_position)
	{
		event_cursor_right(ed);
	}
}

EV_CB_RET 	event_cursor_word_right(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cursor_word_left(EV_CB_ARGS)
{(void)ed;}
