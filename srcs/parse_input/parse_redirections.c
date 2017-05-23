#include "parse_syntax_tree.h"
#include "abstract_list.h"
#include "utils.h"
#include <libft.h>
#include "errors.h"
#include "variable.h"

static int 	get_default_fd(t_redir_type type)
{
	if (type == REDIR_OUTPUT || type == APPEND_OUTPUT)
		return (1);
	else if (type == REDIR_INPUT || type == REDIR_INPUT_HEREDOC)
		return (0);
	return (-1);
}

static t_redirection	*create_redirection(t_token const *tokens, t_token const **end)
{
	t_redirection		*result;

	if (tokens == NULL)
		return (NULL);
	result = memalloc_or_die(sizeof(t_redirection));
	if (tokens->type->id == IO_NUMBER_TOKID)
	{
		result->n = ft_atoi(tokens->str);
		tokens = tokens->next;
	}
	else
		result->n = -1;
	if (tokens == NULL || (tokens->type->id != (t_token_id)REDIR_OUTPUT
					&& tokens->type->id != (t_token_id)REDIR_INPUT
					&& tokens->type->id != (t_token_id)APPEND_OUTPUT
					&& tokens->type->id != (t_token_id)REDIR_INPUT_HEREDOC))
	{
		free(result);
		return (NULL);
	}
	if (result->n == -1)
		result->n = get_default_fd((t_redir_type)tokens->type->id);
	result->type = (t_redir_type)tokens->type->id;
	tokens = tokens->next;
	if (tokens == NULL || tokens->type->id != TOKEN_TOKID)
	{
		free(result);
		return (NULL);
	}
	result->word = ft_strdup(tokens->str);
	*end = tokens->next;
	return (result);
}

t_redirection			*parse_redirections(t_token const *tokens\
											, t_token **remains)
{
	t_redirection	*result;
	t_redirection	**next_addr;
	t_token			**next_remain;

	set_error(NO_ERROR);
	*remains = NULL;
	result = NULL;
	next_addr = &result;
	next_remain = remains;
	while (tokens != NULL)
	{
		*next_addr = create_redirection(tokens, &tokens);
		if (*next_addr == NULL)
		{
			// if the word is not part of redirection and a valid word,
			// copy it in remains
			if (tokens->type->id != TOKEN_TOKID)
			{
				delete_redirections(&result);
				set_error(UNEXPECTED_TOKEN);
				return (NULL);
			}
			*next_remain = copy_token(tokens);
			next_remain = &(*next_remain)->next;
			tokens = tokens->next;
		}
		else
			next_addr = &(*next_addr)->next;
	}
	return (result);
}
