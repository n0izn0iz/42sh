#ifndef HISTORY_DEBUG_H
#define HISTORY_DEBUG_H

#include <libft.h>
#include "shell_env.h"
#include "history_options.h"
#include "range.h"

// #define HISTORY_DEBUG

void			print_history_options(t_hist_opt *options);
void			print_range(t_range *range);
void			print_subst(t_str_subst subst);

#endif
