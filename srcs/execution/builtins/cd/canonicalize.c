/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 17:49:16 by asenat            #+#    #+#             */
/*   Updated: 2017/06/23 17:49:24 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/builtins/cd.h"

static int			try_remove_dot_dots(t_strlist **cmpnts_addr)
{
	t_strlist	*component;
	t_strlist	*start;

	component = *cmpnts_addr;
	start = component;
	while (component != NULL && component->next != NULL)
	{
		if (comp_is_dot_dot(component->next->str) &&
				component->str[0] != '/' && !comp_is_dot_dot(component->str))
		{
			if (!comp_is_directory(start, component))
				return (EXIT_FAILURE);
			*cmpnts_addr = component->next->next;
			component->next->next = NULL;
			strlist_delete(&component);
		}
		else
			cmpnts_addr = &component->next;
		component = *cmpnts_addr;
	}
	return (EXIT_SUCCESS);
}

static void			simplify(t_strlist *components)
{
	size_t	u;

	if (components == NULL)
		return ;
	if (components->str[0] == '/' && components->str[1] == '/' && components->str[2] == '/')
		strfreeswap(&components->str, ft_strdup("/"));
	components = components->next;
	while (components != NULL && components->next != NULL)
	{
		u = 0;
		while (components->str[u] != '\0' && components->str[u] != '/')
			u++;
		if (components->str[u] != '\0')
			components->str[u + 1] = '\0';
		components = components->next;
	}
	if (components != NULL)
	{
		u = 0;
		while (components->str[u] != '\0' && components->str[u] != '/')
			u++;
		components->str[u] = '\0';
	}
}

/*
** The curpath value shall then be converted to canonical form as follows, considering each component from beginning to end, in sequence:
**a Dot components and any <slash> characters that separate them from the next component shall be deleted.
**b For each dot-dot component, if there is a preceding component and it is neither root nor dot-dot, then:
**i If the preceding component does not refer (in the context of pathname resolution with symbolic links followed) to a directory,
**then the cd utility shall display an appropriate error message and no further steps shall be taken.
**
**ii The preceding component, all <slash> characters separating the preceding component from dot-dot, dot-dot, and all <slash> characters
**separating dot-dot from the following component (if any) shall be deleted.
**c An implementation may further simplify curpath by removing any trailing <slash> characters that are not also leading <slash> characters,
**replacing multiple non-leading consecutive <slash> characters with a single <slash>, and replacing three or more leading <slash> characters
**with a single <slash>. If, as a result of this canonicalization, the curpath variable is null, no further steps shall be taken.
*/

char				*canonicalize_path(char const *path)
{
	t_strlist	*components;
	char		*result;

	if (!path)
		fatal_error("NULL ptr fed to canonicalize_path()");
	components = break_components(path);
	remove_dots(&components);
	if (try_remove_dot_dots(&components) == EXIT_FAILURE)
	{
		strlist_delete(&components);
		return (NULL);
	}
	simplify(components);
	result = strlist_to_str(components);
	strlist_delete(&components);
	return (result);
}
