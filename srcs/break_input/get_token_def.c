#include <stdlib.h>
#include "token_def.h"
#include "uint.h"

static t_token_def const	g_token_defs[TOKEN_DEF_COUNT] =
{
	{ TOKEN_TOKID, "TOKEN", NULL},
	{ WORD_TOKID, "WORD", NULL},
	{ ASSIGNMENT_WORD_TOKID, "ASSIGNMENT_WORD", NULL},
	{ IO_NUMBER_TOKID, "IO_NUMBER", NULL},
	{ NEWLINE_TOKID, "NEWLINE", "\n"},
	{ SEMI_TOKID, "SEMI", ";"},
	{ OR_TOKID, "OR", "|"},
	{ LESS_TOKID, "LESS", "<"},
	{ DLESS_TOKID, "DLESS", "<<"},
	{ GREAT_TOKID, "GREAT", ">"},
	{ AND_IF_TOKID, "AND_IF", "&&"},
	{ OR_IF_TOKID, "OR_IF", "||"},
	{ DGREAT_TOKID, "DGREAT", ">>"}
};

t_token_def const			*get_token_defs(void)
{
	return (g_token_defs);
}

t_token_def const			*get_token_def(t_token_id id)
{
	t_uint	u;

	u = 0;
	while (u < TOKEN_DEF_COUNT)
	{
		if (g_token_defs[u].id == id)
			return (g_token_defs + u);
		u += 1;
	}
	return (NULL);
};
