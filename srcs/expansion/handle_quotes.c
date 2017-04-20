#include "expansion.h"

void 				handle_quotes(char c, char *quoted)
{
	// if (c == '\\')
	// 	;
	if (c == '\'')
	{
		if (*quoted & IS_QU_SIMPLE)
			*quoted -= IS_QU_SIMPLE;
		else
			*quoted |= IS_QU_SIMPLE;
	}
	else if (c == '\"')
	{
		if (*quoted & IS_QU_DOUBLE)
			*quoted -= IS_QU_DOUBLE;
		else
			*quoted |= IS_QU_DOUBLE;
	}
}
