# include <libft.h>
# include "utils.h"
# include "abstract_list.h"
# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

void free_editor(t_editor *ed) 
{
	free_string(ed->string);
	free(ed->prompt);
}

char *edit_input()
{
	char						buf[EVENT_STR_MAX_LEN + 1];
	ssize_t						ret;
	t_event_callback_def const	*def;
	t_editor					*ed;
	char						*line;

	ft_start_termcaps();
	ed = get_editor();
	init_editor();
	ed->need_refresh = true;
	refresh_line(ed);

	while ((ret = read(0, buf, EVENT_STR_MAX_LEN)) > 0)
	{
		buf[ret] = '\0';
		def = get_matching_event_callback(buf);
		if (def)
		{
			def->callback(ed);
			if (def->id == NEWLINE_EVID)
				break ;
		}
		else
		{
			if (ft_isprint(buf[0]))
				add_to_string(ed, buf[0]);
		}
		refresh_line(ed);
	}

	ft_close_termcaps();
	line = get_string_from_list(ed->string);
	free_editor(ed);
	return (line);
}
