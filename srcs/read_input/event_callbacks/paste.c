#include "event_callback_def.h"

EV_CB_RET	event_paste(EV_CB_ARGS)
{
	size_t i;

	if (if_on_multiline(ed))
		return ;
	i = -1;
	if (ed->selected_string)
	{
		while (ed->selected_string[++i])
			add_to_string(ed, ed->selected_string[i]);
	}
}
