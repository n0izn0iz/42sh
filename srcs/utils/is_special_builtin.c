#include <stdbool.h>
#include <libft.h>

bool	is_special_builtin(char *builtin)
{
	static char *special_builtins[] = {"exit", "unset", "export", NULL};
	size_t		i;

	i = 0;
	while (special_builtins[i])
	{
		if (!ft_strcmp(special_builtins[i], builtin))
			return (true);
		i++;
	}
	return (false);
}
