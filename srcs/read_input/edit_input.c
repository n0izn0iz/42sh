# include <libft.h>
# include "utils.h"
# include "abstract_list.h"
# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

void move_start(t_editor *ed)
{
	ed->string_size = list_count((t_abstract_list*)ed->string);
	int size = ed->prompt_size + ed->cursor_position;

	while (size > ed->term->width)
	{
		size -= ed->term->width;
		ft_putstr(ed->term->move_up);
	}
	ft_putstr(ed->term->move_cursor_begining);
}

void restore_old_cursor_position(t_editor *ed, size_t old_position)
{
	ed->cursor_position = ed->string_size;
	while (ed->cursor_position > old_position)
	{
		event_cursor_left(ed);
	}
}

void refresh_line(t_editor *ed)
{
	char		*line;
	size_t		tmp;

	if (ed->need_refresh == true)
	{
		ed->need_refresh = false;
		move_start(ed);
		ft_putstr(ed->term->clear_line);

		line = get_string_from_list(ed->string);
		ft_putstr(ed->prompt);
		tmp = ed->cursor_position;
		if (ed->in_selection == true)
			ed->selected_string_end = ed->cursor_position;
		put_highlighted_line(ed, line);
		ed->cursor_position = ft_strlen(line);
		free(line);
		if (check_cursor_if_margin(ed))
		{
			ft_putchar('\n');
		}
		ed->cursor_position = tmp;
		restore_old_cursor_position(ed, ed->cursor_position);
	}
}

void free_editor(t_editor *ed)
{
	free_string(ed->string);
	free(ed->prompt);
	free(ed->term);
}

void add_buffer_to_string(t_editor *ed, char buf[])
{
	size_t	i;

	i = -1;
	while (buf[++i])
	{
		if (ft_isprint(buf[i]) || buf[i] == '\t')
			add_to_string(ed, buf[i]);
	}
}

char *edit_input()
{
	char						buf[EVENT_STR_MAX_LEN + 1];
	int							ret;
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
			add_buffer_to_string(ed, buf);
		}
		refresh_line(ed);
	}

	ft_close_termcaps();
	line = get_string_from_list(ed->string);
	free_editor(ed);
	return (line);
}
