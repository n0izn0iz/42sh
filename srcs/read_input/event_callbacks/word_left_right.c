#include "event_callback_def.h"
#include <libft.h>

static bool		is_white(char c)
{
	if (!c)
		return (false);
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	return (false);
}

static size_t	get_next_word(t_editor *ed)
{
	char	*str;
	size_t	pos;

	str = get_string_from_list(ed->string);
	pos = ed->cursor_position;
	if (pos >= ed->string_size)
		return (pos);
	pos++;
	if (pos > ft_strlen(str))
		return (ed->cursor_position);
	while (str[pos] && is_white(str[pos]))
		pos++;
	while (str[pos] && !is_white(str[pos]))
		pos++;
	free(str);
	return (pos);
}

static size_t	get_previous_word(t_editor *ed)
{
	char	*str;
	size_t	pos;

	str = get_string_from_list(ed->string);
	pos = ed->cursor_position;
	if (pos <= 0)
		return (0);
	pos--;
	while (pos > 0 && str[pos] && !is_white(str[pos]))
		pos--;
	while (pos > 0 && str[pos - 1] && is_white(str[pos - 1]))
		pos--;
	free(str);
	return (pos);
}

EV_CB_RET 	event_cursor_word_right(EV_CB_ARGS)
{
	t_vec2i pos;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = get_next_word(ed);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}

EV_CB_RET 	event_cursor_word_left(EV_CB_ARGS)
{
	t_vec2i pos;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = get_previous_word(ed);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}
