
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
	int	exit_code;

	exit_code = 0;
	while (redirect)
	{
		if (redirect->ttype == TT_RE_INPUT)
		{
			exit_code = redirect_input(redirect);
		}
		else if (redirect->ttype == TT_RE_OUTPUT)
		{
			exit_code = redirect_output(redirect);
		}
		else if (redirect->ttype == TT_RE_APPEND)
		{
			exit_code = redirect_append(redirect);
		}
		else if (redirect->ttype == TT_HEREDOC)
		{
			printf("heredoc missing :((((((\n");
		}
		if (exit_code != 0)
			return (exit_code);
		redirect = redirect->next;
	}
	return (exit_code);
}
