/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:09:36 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 17:22:15 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input/editor/editor.h"
#include "abstract_list.h"
#include "utils.h"
#include "break_input/quoting.h"
#include "expansion.h"

#define SIMPLE_QUOTE '\''
#define DOUBLE_QUOTE '"'
#define BACKSLASH '\\'

static char *erase_char(char *str)
{
	if (str[0] != '\0')
		ft_strcpy(str, str + 1);
	return (str);
}

static bool	backslash_shall_retain_meaning(char next_char)
{
	if (next_char == '$'
	  || next_char == SIMPLE_QUOTE
	  || next_char == DOUBLE_QUOTE
	  || next_char == BACKSLASH
	  || next_char == '\n')
		return (true);
	else
		return (false);
}

static char *find_double_quotes_end_and_remove_backslashes(char *str)
{
	char current_char;

	while ((current_char = str[0]) != DOUBLE_QUOTE && current_char != '\0')
	{
		if (current_char == BACKSLASH && backslash_shall_retain_meaning(str[1]))
			erase_char(str);
		str++;
	}
	if (current_char == '\0')
		fatal_error("couldn't find matching double quote during quote removal");
	return (str);
}

static char *remove_double_quotes(char *str)
{
	erase_char(str);
	str = find_double_quotes_end_and_remove_backslashes(str);
	erase_char(str);
	return (str);
}

static char *find_simple_quotes_end(char *str)
{
	char current_char;

	while ((current_char = str[0]) != SIMPLE_QUOTE && current_char != '\0')
		str++;
	if (current_char == '\0')
		fatal_error("couldn't find matching simple quote during quote removal");
	return (str);
}

static char *remove_simple_quotes(char *str)
{
	erase_char(str);
	str = find_simple_quotes_end(str);
	erase_char(str);
	return (str);
}

static char *find_and_remove_quote(char *str)
{
	char first_char;

	first_char = *str;
	if (first_char == SIMPLE_QUOTE)
		return (remove_simple_quotes(str));
	else if (first_char == DOUBLE_QUOTE)
		return (remove_double_quotes(str));
	else if (first_char == BACKSLASH)
		return (erase_char(str) + 1);
	else
		return (str + 1);
}

static bool			has_quotes(char *str)
{
	while (*str != '\0')
	{
		if (is_quote(*str))
			return (true);
		str++;
	}
	return (false);
}

void		quote_removal(char **word_ptr)
{
	char			*word;

	if (word_ptr == NULL)
		fatal_error("NULL word_ptr fed to quote_removal");
	word = *word_ptr;
	if (word == NULL)
		fatal_error("NULL word fed to quote_removal");
	if (has_quotes(word))
		while (*word != '\0')
			word = find_and_remove_quote(word);
}
