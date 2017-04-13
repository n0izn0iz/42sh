#include "libft.h"
#include "tabenv.h"

/*
** Browse env var
*/

char	*get_tenv(char **env, char *var)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		if (ft_strcmp(env[i], var) == 61)
			return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}

/*
** Split, check good format
** remove env var if already exists
** add env var
*/

char	**ft_setenv(char **env, char *namevalue)
{
	char	**name;

	name = ft_strsplit(namevalue, '=');
	if (env != NULL && get_tenv(env, name[0]) != NULL)
		env = del_env(env, name[0]);
	ft_freetabchar(name);
	env = add_env(env, namevalue);
	return (env);
}

char	**add_env(char **env, char *new_env)
{
	int		i;
	char	**nenv;

	nenv = (char**)memalloc_or_die(sizeof(char*) * (ft_tablen(env) + 2));
	i = 0;
	if (env != NULL)
		while (env[i] != NULL)
		{
			nenv[i] = env[i];
			i += 1;
		}
	nenv[i] = ft_strdup(new_env);
	nenv[++i] = NULL;
	free(env);
	return (nenv);
}

/*
** Copy every line till encounter the one which must be deleted
** Free memory of deleted line
** Continue copying ever line till the end
*/

char	**del_env(char **env, char *old_env)
{
	int		i;
	char	**nenv;

	nenv = (char**)memalloc_or_die(sizeof(char*) * (ft_tablen(env) + 1));
	i = -1;
	while (env[++i] != NULL && ft_strcmp(env[i], old_env) != '=')
		nenv[i] = env[i];
	ft_strdel(&env[i]);
	while (env[i + 1] != NULL)
	{
		nenv[i] = env[i + 1];
		i++;
	}
	free(env);
	nenv[i] = NULL;
	return (nenv);
}

int		isenv(char *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] < 'A' || ('Z' < str[i] && str[i] < '_') ||
				('_' < str[i] && str[i] < 'a') || str[i] > 'z')
			return (0);
	return (1);
}
