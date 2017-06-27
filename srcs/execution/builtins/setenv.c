/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:52:45 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:52:47 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_def.h"
#include <libft.h>
#include <signal.h>
#include "shell_env.h"
#include "abstract_list.h"
#include "variable.h"

int		builtin_setenv(int argc, char **argv)
{
	t_variable	**env;

	env = &get_shell_env()->variables;
	if (argc == 2 || argc == 3)
	{
		if (ft_strchr(argv[1], '='))
		{
			ft_dprintf(STDERR_FILENO, "It's forbidden to use '='\n");
			return (STATUS_FAILURE);
		}
		if (argc == 2)
		{
			if (setenv_as(env, argv[1], "", true) == STATUS_SUCCESS)
				return (STATUS_SUCCESS);
		}
		else
		{
			if (setenv_as(env, argv[1], argv[2], true) == STATUS_SUCCESS)
				return (STATUS_SUCCESS);
		}
	}
	else
		ft_dprintf(STDERR_FILENO, "Usage: setenv <key> <value>\n");
	return (STATUS_FAILURE);
}

int		setenv_as(t_variable **env, char *name, char *value, bool exported)
{
	if (env && ft_strlen(name) > 0)
	{
		if (variable_exist(*env, name))
		{
			if (variable_is_overwritable(*env, name))
				unsetenv_as(env, name);
			else
				return (STATUS_SUCCESS);
		}
		list_push_back((t_abstract_list**)&env,
			(t_abstract_list*)create_variable(name, value, exported, true));
		return (STATUS_SUCCESS);
	}
	return (STATUS_FAILURE);
}
