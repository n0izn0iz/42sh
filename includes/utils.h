#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include "uint.h"
# include "read_input/editor/editor_struct.h" // move

# define ARG_STOP "--"

void					print_non_ascii_str(char const *str);
void					print_non_ascii_char(char c);
void					event_callback_test(void);
char					*strdup_until(char const *src, char const *stop);
bool					is_posix_blank(char c);
void					print_n_char(char c, size_t n);
void					print_n_char_fd(char c, size_t n, int fd);
bool					str_is_digits(char const *str);
bool					is_circumflex(char c);
bool					is_bang(char c);
char					*str_in_str(char *find, char *str, t_uint start, \
									bool must_start);
int 					find_and_replace(char **str, char *to_find, \
										char *replace, t_uint start);
void					str_join_with_space(char **str, char *to_join);
void					str_add_space(char **str);
size_t					number_len(char *str);
char					**copy_array(char **array, size_t start, int end);
char					*array_to_str(char **array);
t_string				*str_to_list(char *str);
void					free_ptr_array(void *ptr_array);
void					fatal_error(char const *str);
t_uchar					get_last_exit_status(void);
void					set_last_exit_status(t_uchar status);
void					wait_for_childs();
char					*get_options_core(int ac, char **av);
bool					is_an_option(char **argv, int pos);
bool					is_an_argument(char **argv, int pos);
bool					check_only_allowed_option(char *option, char *allowed);
size_t					number_of_argument(char **argv);

#endif
