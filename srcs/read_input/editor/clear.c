# include <libft.h>
# include "utils.h"
# include "abstract_list.h"
# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

void move_start(EV_CB_ARGS)
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

void restore_old_cursor_position(t_editor *ed)
{
	ed->cursor_position = ed->string_size;
	while (ed->cursor_position > ed->old_position)
	{
		event_cursor_left(ed);
	}
}

void clear_line(EV_CB_ARGS)
{
	move_start(ed);
	ft_putstr(ed->term->clear_line);
	ed->old_position = ed->cursor_position;
}

void put_line(EV_CB_ARGS)
{
	char		*line;

	line = get_string_from_list(ed->string);
	ed->cursor_position = ft_strlen(line);
	ft_putstr(ed->prompt);
	ft_putstr(line);
	free(line);
	if (check_cursor_if_margin(ed))
	{
		ft_putchar('\n');
	}
}

void refresh_line(EV_CB_ARGS)
{
	if (ed->need_refresh == true)
	{
		ed->need_refresh = false;
		clear_line(ed);
		put_line(ed);
		restore_old_cursor_position(ed);	
	}
}