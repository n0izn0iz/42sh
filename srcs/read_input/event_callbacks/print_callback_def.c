#include "event_callback_def.h"
#include <libft.h>
#include "utils.h"

void								print_event_callback_def(
	t_event_callback_def const *def)
{
	if (def != NULL)
	{
		ft_printf("id:%d, name:\"%s\", str:\"", def->id, def->name);
		print_non_ascii_str(def->str);
		ft_printf("\", callback:%p\n", def->callback);
	}
}
