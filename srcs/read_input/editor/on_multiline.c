# include <libft.h>
# include "read_input/event_callbacks/event_callback_def.h"

bool		if_on_multiline(EV_CB_ARGS)
{
	// char	*str;
	int		nb;

	// str = get_string_from_list(ed->string);
	// str = get_string_from_list(ed->string);
	nb = ft_count_char(ed->string_cstr, '\n');
	// free(str);
	if (nb > 0)
		return (true);
	return (false);
}
