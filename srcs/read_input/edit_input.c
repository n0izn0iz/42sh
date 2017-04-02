# include <libft.h>
# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

static void	add_buffer_to_string(t_editor *ed, char buf[])
{
	size_t	i;

	i = -1;
	while (buf[++i])
	{
		if (ft_isprint(buf[i]) || buf[i] == '\t')
			add_to_string(ed, buf[i]);
	}
}

#include <stdio.h>

void		print_cursor_vector(t_editor *ed)
{
	t_vec2i						vec;

	vec = get_cursor_vector(ed);
	dprintf(2, "cx: %d, cy: %d\n", vec.x, vec.y);
}

char 		*edit_input()
{
	char						buf[EVENT_STR_MAX_LEN + 1];
	int							ret;
	t_event_callback_def const	*def;
	t_editor					*ed;

	ft_start_termcaps();
	ed = get_editor();
	init_editor();
	ed->need_refresh = true;
	refresh_line(ed);
	// print_cursor_vector(ed);
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
			add_buffer_to_string(ed, buf);
		}
		refresh_line(ed);
		// print_cursor_vector(ed);
	}

	ft_close_termcaps();
	free_editor(ed);
	return (ed->string_cstr);
}
