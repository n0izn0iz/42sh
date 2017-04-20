#ifndef HISTORY_SUBSTITUTIONS_H
# define HISTORY_SUBSTITUTIONS_H

#include <libft.h>
#include "break_input/token.h"
#include "history/history_def.h"
#include "range.h"

/*
**			history_substitutions.c
*/

int				history_substitution(char **str);

/*
**			get_history_entry.c
*/

char			*get_history_entry(char *designator, t_uint *end);
char			*get_nth_entry(t_history *history, int n);

/*
**			history_search.c
*/

char			*find_in_history(bool must_start, t_history *history, \
							char *str, t_uint *end);
char			*last_hist_search();

/*
**			get_entry_word.c
*/

char			*get_nth_word(char *line, t_uint n);
void 			get_entry_word(char **entry, char *str, t_uint *end);

/*
**			word_range.c
*/

int 			parse_range(char *str, int *i, t_range *range);
void 			range_selection(char *str, int *i, t_range *range, char **words);
char			*get_word_range(char *line, t_range *range);

/*
**			word_designators.c
*/

bool			start_word_designator(char c);
void			parse_word_designators(char *str, int *i, t_range *range, \
										char **entry, char **words);

/*
**			history_tokenizer.c
*/

t_token			*tokenize_for_substitution(char const *input);

/*
**			history_modifiers.c
*/

bool			apply_modifiers(char *modifiers, char **str, t_uint *end, bool *quote);

/*
**			add_quotes.c
*/

void			quote_word(char **word);
void			quote_per_word(char **str);

/*
**			perform_hist_subst
*/

void			quick_substitution(char **str, t_uint *i);
void 			perform_substitution(char **str, char *hist_entry, \
										t_uint *start, t_uint end);

#endif
