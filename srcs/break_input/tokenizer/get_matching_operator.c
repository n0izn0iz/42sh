#include <stdlib.h>
#include "uint.h"
#include "token_def.h"
#include <libft.h>

t_token_def const			*get_matching_operator(char const *str)
{
	t_uint				u;
	t_token_def const	*defs;

	defs = get_token_defs();
	u = 0;
	while (u < TOKEN_DEF_COUNT)
	{
		if (defs[u].str != NULL && ft_strncmp(defs[u].str, str, ft_strlen(str)) == 0)
			return (defs + u);
		u++;
	}
	return (NULL);
}