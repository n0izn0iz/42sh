#include "read_input/editor/editor.h"

void	str_to_list_in_editor(t_editor *ed, char *str)
{
	if (str == NULL)
		return ;
	while (*str)
	{
		add_to_string(ed, *str);
		str++;
	}
}
