#include "event_callback_def.h"
#include <libft.h>

EV_CB_RET 	event_cursor_left(EV_CB_ARGS)
{
	(void)ed;
	if (ed->cursor_position > 0)
	{
		ft_putstr(ed->term->move_left);
		ed->cursor_position--;
	}
}

EV_CB_RET 	event_cursor_right(EV_CB_ARGS)
{
	(void)ed;
	ed->need_refresh = true;
	if (ed->cursor_position < ed->string_size)
	{
		ft_putstr(ed->term->move_right);
		ed->cursor_position++;		
	}
}

EV_CB_RET 	event_cursor_up(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cursor_down(EV_CB_ARGS)
{(void)ed;}
