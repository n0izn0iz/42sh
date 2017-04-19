#include "libft.h"
#include "opt.h"
#include "builtins.h"

/*
** could be use as generic f() for other builtins
** check options presence:
** -e, -E, -s, -n, -esn
*/

int		retrieve_options(int argc, char **argv, t_opt *o, char *opts)
{
	int	i;
	int	j;

	i = 0;
	o->s = false;
	o->n = false;
	o->e = false;
	o->i = false;
	while (++i < argc && argv[i][0] == '-' && argv[i][1] != '-')
	{
		j = 0;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] == 's' && ft_strchr(opts, 's') != NULL)
				o->s = true;
			else if (argv[i][j] == 'n' && ft_strchr(opts, 'n') != NULL)
				o->n = true;
			else if (argv[i][j] == 'e' && ft_strchr(opts, 'e') != NULL)
				o->e = true;
			else if (argv[i][j] == 'i' && ft_strchr(opts, 'i') != NULL)
				o->i = true;
			else
				return (i - 1);
		}
	}
	return (i - 1);
}
