# include <stdbool.h>
# include <libft.h>

bool is_an_option(char **argv, int pos)
{
	int		i;
	int		j;

	if (!argv || ft_tablen(argv) <= 1)
		return (false);
	i = 0;
	while (++i <= pos && argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			return (false);
		if (argv[i][0] == '-' && argv[i][1] != '-')
		{
			j = 0;
			while (argv[i][++j])
			{
				if (ft_isalpha(argv[i][j]))
				{
					if (i == pos)
						return (true);
				}
			}
		}
	}
	return (false);
}
