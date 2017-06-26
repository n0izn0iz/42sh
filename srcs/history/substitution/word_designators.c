
#include "utils.h"
#include "range.h"

#include "break_input/tokenizer.h"
#include "history_substitutions.h"

bool			start_word_designator(char c)
{
	if (c == ':' || c == '^' || c == '%' || c == '*' || c == '-' || c == '$')
		return (true);
	return (false);
}
