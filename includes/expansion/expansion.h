#ifndef EXPANSION_H
# define EXPANSION_H

#include "strlist.h"

// #define EXPANSION_DEBUG

#define IS_QU_SIMPLE 0b0001
#define	IS_QU_DOUBLE 0b0010

void				expand_cmd_words(char ***words_addr);
char				*command_substition(char const *word);
t_strlist			*field_splitting(char const *word);
void				quote_removal(char **word);
void 				handle_quotes(char c, char *quoted);

#endif
