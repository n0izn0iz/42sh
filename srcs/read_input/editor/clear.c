# include <libft.h>
# include "read_input/event_callbacks/event_callback_def.h"

void clear_line(EV_CB_ARGS)
{
	char	*str;
	
	move_start(ed);
	////refresh
	free(ed->string_cstr);
	ed->string_cstr = get_string_from_list(ed->string);
	ed->pos = get_cursor_vector(ed);

	str = ft_strjoin(ed->prompt, ed->string_cstr);
	ed->string_split = ft_strsplit(str, '\n');
	free(str);
	///
	ft_putstr(ed->term->clear_line);
}

void free_editor(EV_CB_ARGS)
{
	free_string(ed->string);
	free(ed->prompt);
}
