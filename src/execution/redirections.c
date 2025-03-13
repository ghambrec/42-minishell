
#include "minishell.h"

int	open_redirections(t_redirection *redirect)
{
	int	fd;

	while (redirect)
	{
		if (redirect->ttype == TT_RE_OUTPUT)
		{
			fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(redirect->filename);
				return (errno);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}


		redirect = redirect->next;
	}

	return (0);
}
