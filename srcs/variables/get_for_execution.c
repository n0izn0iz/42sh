#include <libft.h>
#include "shell_env.h"
#include "abstract_list.h"

static size_t	get_number_of_exported()
{
	t_variable	*e;
	size_t		size;

	e = get_shell_env()->variables;
	size = 0;
	while (e)
	{
		if (e->exported == true)
			size++;
		e = e->next;
	}
	return (size);
}

static bool		is_in_assignment(t_variable *assignments, char *name)
{
	if (!assignments || ft_strlen(name) <= 0)
		return (false);
	while (assignments)
	{
		if (!ft_strcmp(assignments->name, name))
		{
			return (true);
		}
		assignments = assignments->next;
	}
	return (false);
}

static size_t	number_in_assignment(t_variable	*e, t_variable *assignments)
{
	size_t	nb;

	if (!e || !assignments)
		return (0);
	nb = 0;
	while (e)
	{
		if (is_in_assignment(assignments, e->name))
			nb++;
		e = e->next;
	}
	return (nb);
}

static char		**create_envp(t_variable *e, size_t size)
{
	size_t		i;
	char		**envp;

	if (!e)
		return (NULL);
	envp = memalloc_or_die(sizeof(char *) * (size + 1));

	i = 0;
	while (e)
	{
		if (e->exported == true)
		{
			envp[i] = ft_strjoinf(e->name, ft_strjoin("=", e->value), 2);
			i++;
			envp[i] = NULL;
		}
		e = e->next;
	}
	return (envp);
}

char	**get_variables_for_execution(t_variable *assignments)
{
	size_t	size;
	size_t	reassigned;

	t_variable	*e = get_shell_env()->variables;
	t_variable	*ee = (t_variable *)list_dup_until((t_abstract_list*)e, NULL, sizeof(t_variable));

	size = get_number_of_exported();
	reassigned = number_in_assignment(ee, assignments);
	if (assignments)
		size += list_count((t_abstract_list *)assignments) - reassigned;
	if (!size)
		return (NULL);

	while (assignments)
	{
		setenv_as(&ee, assignments->name, assignments->value);
		assignments = assignments->next;
	}
	return (create_envp(ee, size));
}
