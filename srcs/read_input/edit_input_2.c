#include <libft.h>
#include <signal.h>
#include "read_input/editor/editor.h"
#include "read_input/event_callbacks/event_callback_def.h"
#include "read_input/termcap/init_deinit.h"

static void	add_buffer_to_string(t_editor *ed, char buf[])
{
	size_t	i;

	i = -1;
	while (buf[++i])
	{
		if (ft_isprint(buf[i]))
			add_to_string(ed, buf[i]);
	}
}

void		print_cursor_vector(t_editor *ed)
{
	t_vec2i						vec;

	vec = get_cursor_vector(ed);
	ft_dprintf(2, "cx: %d, cy: %d\n", vec.x, vec.y);
}

char		*start_rescue_mode(void)
{
	char	*line;

	ft_close_termcaps();
	ft_printf("[RESCUE MODE]$ ");
	line = ft_getline(STDIN_FILENO);
	return (line);
}

char		*start_normal_mode(t_editor *ed)
{
	char						buf[EVENT_STR_MAX_LEN + 1];
	int							ret;
	t_event_callback_def const	*def;

	ed->need_refresh = true;
	put_line(ed);
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
			close_history(ed);
			add_buffer_to_string(ed, buf);
		}
		refresh_line(ed);
	}
	ft_close_termcaps();
	return (get_string_from_list(ed->string));
}
