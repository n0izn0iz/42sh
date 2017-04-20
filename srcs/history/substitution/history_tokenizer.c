#include "shell_env.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "break_input/tokenizer.h"

/*
**	slightly modified tokenizer to handle 'bli bla "!!' case
**	(bang isn't quoted with double quotes, so substitution IS made)
**	add bool to original tokenizer?
*/

void			add_quote_to_token(t_token *token)
{
	char *tmp;

	while (token->next)
		token = token->next;
	tmp = ft_strjoin(token->str, "\"");
	ft_strdel(&token->str);
	token->str = ft_strdup(tmp);
	ft_strdel(&tmp);
	set_error(NO_ERROR);
	get_shell_env()->last_unmatched = NO_ERROR;
}

void			add_quote_token(t_tokenizer_state const state, t_token *result)
{
	t_token		*token;
	char		*str;
	char		*tmp;

	tmp = ft_strdup(state.current_char);
	str = ft_strtrim(tmp);
	ft_strdel(&tmp);
	token = construct_token(str, *state.current_char);
	list_push_back((t_abstract_list**)&result
				, (t_abstract_list*)token);
	ft_strdel(&str);
	set_error(NO_ERROR);
}

t_token			*tokenize_for_substitution(char const *input)
{
	t_token						*result;
	t_tokenizer_state			state;

	set_error(NO_ERROR);
	result = NULL;
	if (input != NULL)
	{
		ft_bzero(&state, sizeof(t_tokenizer_state));
		state.input = ft_strdup(input);
		state.current_char = state.input;
		while (*state.current_char != '\0')
		{
			apply_rules(&state);
			if (get_error() != NO_ERROR)
			{
				if (get_error() == UNMATCHED_DOUBLE_QUOTE)
					break ;
				free(state.input);
				delete_all_tokens(&state.result);
				return (NULL);
			}
		}
		delimit_token(&state);
		result = state.result;
		if (get_error() == UNMATCHED_DOUBLE_QUOTE)
		{
			if (*state.current_char == '"' && *(state.current_char - 1) == ' ')
				add_quote_token(state, result);
			else if (*state.current_char == '"')
				add_quote_to_token(result);
		}
		free(state.input);
	}
	return (result);
}
