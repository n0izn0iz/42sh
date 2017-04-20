#ifndef HISTORY_OPTIONS_H
# define HISTORY_OPTIONS_H

#include <stdbool.h>
// #include "history.h"

#define A_OPT 0b1000
#define N_OPT 0b0100
#define R_OPT 0b0010
#define W_OPT 0b0001

typedef	struct 	s_hist_opt
{
	char		anrw;
	bool		c;
	bool		d;
	bool		p;
	bool		s;
	char		*offset;
	char		*filename;
	char		**args;
	int 		ac;
}				t_hist_opt;

bool			get_hist_options(char *c, t_hist_opt *options);
void			free_history_options(t_hist_opt *options);

#endif
