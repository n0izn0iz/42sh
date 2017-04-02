# include <libft.h>
# include "read_input/event_callbacks/event_callback_def.h"

void move_start(EV_CB_ARGS)
{
	t_vec2i	vec;

	vec = get_cursor_vector(ed);

	if (vec.x > 0)
	{
		while (vec.y-- > 0)
			ft_putstr(ed->term->move_up);
	}
	else
	{
		while (vec.y-- > 1)
			ft_putstr(ed->term->move_up);
	}
	ft_putstr(ed->term->move_cursor_begining);
}

static void print_command_string(EV_CB_ARGS, size_t term_width)
{
	size_t	u;

	u = 0;
	while (ed->string_split[u] != NULL)
	{
		put_highlighted_line(ed, ed->string_split[u]);
		if (ft_strlen(ed->string_split[u]) % term_width == 0)
			ft_putchar('\n');
		if (ed->string_split[u + 1] != NULL)
			ft_putchar('\n');
		u++;
	}
}

void put_line(EV_CB_ARGS)
{
	print_command_string(ed, ed->term->width);
	ed->old_position = ed->cursor_position;
	ed->cursor_position = ft_strlen(ed->string_cstr);
}

static void restore_old_cursor_position(EV_CB_ARGS, t_vec2i old_pos)
{
	move_cursor(vec2i_sub(old_pos, ed->pos), ed->term);
}

void refresh_line(EV_CB_ARGS)
{
	if (ed->need_refresh == true)
	{
		ed->need_refresh = false;
		ft_putstr(ed->term->hide_cursor);
		clear_line(ed);
		put_line(ed);
		restore_old_cursor_position(ed, get_cursor_vector(ed));
		ed->cursor_position = ed->old_position;
		ft_putstr(ed->term->show_cursor);
		ft_freetabchar(ed->string_split);
	}
}
