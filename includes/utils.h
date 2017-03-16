#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>

void						print_non_ascii_str(char const *str);
void						print_non_ascii_char(char c);
void						event_callback_test(void);
void						*memalloc_or_die(size_t size);
char						*strdup_until(char const *src, char const *stop);
bool						is_posix_blank(char c);

#endif
