
#include "minishell.h"

int	redirect_input(t_redirection *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(redirect->filename);
		return (errno);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redirect_output(t_redirection *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(redirect->filename);
		return (errno);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirect_append(t_redirection *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redirect->filename);
		return (errno);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	open_redirections(t_redirection *redirect)
{
	while (redirect)
	{
		if (redirect->ttype == TT_RE_INPUT)
		{
			return (redirect_input(redirect));
		}
		else if (redirect->ttype == TT_RE_OUTPUT)
		{
			return (redirect_output(redirect));
		}
		else if (redirect->ttype == TT_RE_APPEND)
		{
			return (redirect_append(redirect));
		}
		else if (redirect->ttype == TT_HEREDOC)
		{
			printf("heredoc missing :((((((\n");
		}
		redirect = redirect->next;
	}
	return (0);
}
