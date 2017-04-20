# include <stdbool.h>
# include "libft.h"

bool	check_only_allowed_option(char *option, char *allowed)
{
	size_t	i;

	if (ft_strlen(option) <= 0 && ft_strlen(allowed) <= 0)
		return (true);
	if (ft_strlen(option) <= 0)
		return (true);
	if (ft_strlen(allowed) <= 0)
		return (false);
	i = -1;
	while (option[++i])
	{
		if (!ft_strchr(allowed, option[i]))
			return (false);
	}
	return (true);
}

char	*get_options_core(int ac, char **av)
{
	char	*arg;
	int		i;
	int		j;

	if (ac <= 1 || !av || ft_tablen(av) <= 1)
		return (NULL);
	arg = NULL;
	i = 0;
	while (++i < ac && av[i])
	{
		if (av[i][0] == '-' && av[i][1] == '-')
			break;
		if (av[i][0] == '-' && av[i][1] != '-')
		{
			j = 0;
			while (av[i][++j])
			{
				if (ft_isalpha(av[i][j]))
				{
					if (!ft_strchr(arg, av[i][j]))
						arg = ft_strjoinf(arg, ft_strndup(&av[i][j], 1), 3);
				}
				else
				{
					free(arg);
					ft_dprintf(2, "Bad argument: %s\n", &av[i][1]);
					return ((char*)-1);
				}
			}
		}
	}
	return (arg);
}
