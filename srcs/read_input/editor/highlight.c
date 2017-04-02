#include "read_input/editor/editor.h"
#include <libft.h>

void put_highlighted_line(t_editor *ed, char* line)
{
	size_t	i;
	size_t	cur;
	size_t	start;
	size_t	end;
	size_t	offset;

	if (!line || ft_strlen(line) <= 0)
		return ;
	offset = ft_strlen(ed->prompt);
	start = ed->selected_string_start + offset;
	end = ed->selected_string_end + offset;
	cur = ed->cursor_position + offset;
	i = -1;
	if (ed->in_selection)
	{
		while (line[++i])
		{
			if ((i >= start && i < cur) || (i < start && i >= cur))
			{
				ft_putcharc(4, 3, line[i]);
			}
			else
			{
				ft_putchar(line[i]);
			}
		}
	}
	else
	{
		ft_putstr(line);
	}
}
