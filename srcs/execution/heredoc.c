#include "heredoc.h"
#include <libft.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
** Launch heredoc: double left redirection <<
** retrieve text through a prompt
** write the text on the pipe
** wait the fork
*/

int	prompt_redirection_init(char *eof)
{
	char	*txt;
	int		*pipefd;

	txt = prompt_heredoc(eof);
	pipefd = (int*)memalloc_or_die(sizeof(int) * 2);
	pipe(pipefd);
	if (fork() == 0)
	{
		close(pipefd[0]);
		ft_putstr_fd(txt, pipefd[1]);
		ft_strdel(&txt);
		exit(0);
	}
	wait(NULL);
	close(pipefd[1]);
	return (pipefd[0]);
}

/*
** prompt to enter text, get entered lines
** join them till it encounter the end of file string except first time
** read, join the buffer till it encounter ENTER
** if ctrl + d: print '\n'; return txt
** return the text
*/

char	*prompt_heredoc(char *eof)
{
	char	*txt;
	char	*cmd;
	int	i;

	i = 0;
	txt = ft_strnew(0);
	cmd = ft_strnew(0);
	while (ft_strcmp(cmd, eof) != 0)
	{
		if (i > 0)
		{
			txt = ft_strjoinf(txt, ft_strjoinf(cmd, "\n", 1), 3);
			cmd = ft_strnew(0);
		}
		ft_putchar('>');
		if (here_edition(&cmd) == 0)
		{
			ft_putchar('\n');
			return (ft_strjoinf(txt, ft_strjoinf(cmd, "\n", 1), 3));
		}
		i += 1;
	}
	ft_strdel(&cmd);
	return (txt);
}

/*
** break loop if encounter ENTER
** join the buffer
*/

int		here_edition(char **cmd)
{
	int		ret;
	char		*key;

	key = ft_strnew(4);
	while ((ret = read(0, key, 1)) > 0)
	{
		if (key[0] == 10)
			break ;
		if (ft_isprint(key[0]) == 1)
		{
			key[ret] = '\0';
			*cmd = ft_strjoinf(*cmd, key, 1);
		}
	}
	ft_strdel(&key);
	return (ret);
}
