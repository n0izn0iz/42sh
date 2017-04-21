# include "builtin_def.h"
# include <stdlib.h>
# include "uint.h"
# include <libft.h>

t_builtin_def const			*get_builtin_defs(void)
{
	static t_builtin_def const defs[BUILTIN_DEF_COUNT] =
	{
	//	ID							NAME					HANDLER FUNCTION
		{ CD_BUID,					"cd",					builtin_cd },
		{ ECHO_BUID,				"echo",					builtin_echo },
		{ EXIT_BUID,				"exit",					builtin_exit },
		{ SETENV_BUID, 				"setenv",				builtin_setenv },
		{ UNSETENV_BUID, 			"unsetenv",				builtin_unsetenv },
		{ SET_BUID, 				"set",					builtin_set },
		{ EXPORT_BUID,				"export",				builtin_export },
		{ UNSET_BUID, 				"unset",				builtin_unset },
		{ HISTORY_BUID,				"history",				builtin_history },
		{ ENV_BUID,				"env",					builtin_env }
	};
	return (defs);
}

t_builtin_def const			*get_matching_builtin(char const *str)
{
	t_uint				u;
	t_builtin_def const	*defs;

	if (str != NULL)
	{
		defs = get_builtin_defs();
		u = 0;
		while (u < BUILTIN_DEF_COUNT)
		{
			if (defs[u].name != NULL && ft_strequ(defs[u].name, str))
				return (defs + u);
			u++;
		}
	}
	return (NULL);
}
