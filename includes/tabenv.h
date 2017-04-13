#ifndef TABENV_H
#define TABENV_H

char	*get_tenv(char **env, char *var);
char	**ft_setenv(char **env, char *namevalue);
char	**add_env(char **env, char *new_env);
char	**del_env(char **env, char *old_env);

#endif
