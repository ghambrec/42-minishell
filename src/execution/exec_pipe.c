
#include "minishell.h"

static void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[PIPE_WRITE]);
	close(pipe_fd[PIPE_READ]);
}

int	exec_pipe(t_ast *ast)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;
	int	exit_status;
	int	status;

	exit_status = EXIT_SUCCESS;

	// pipe erstellen
	if (pipe(pipe_fd) == -1)
	{
		perror("Error opening pipe");
		return (errno);
	}
	// pid1 erstellen
	pid1 = fork();
	if (pid1 == -1)
	{
		close_pipe(pipe_fd);
		perror("Error opening child-process");
		return (errno);
	}
	if (pid1 == 0) // sind im child process
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
		close_pipe(pipe_fd);
		exit(exec_ast(ast->left));
	}

	// pid2 erstellen
	pid2 = fork();
	if (pid2 == -1)
	{
		close_pipe(pipe_fd);
		perror("Error opening child-process");
		kill(pid1, SIGTERM);
		return (errno);
	}
	if (pid2 == 0) // sind im child process
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
		close_pipe(pipe_fd);
		exit(exec_ast(ast->right));
	}
	close_pipe(pipe_fd);

	set_sigaction(SIGINT, handle_sigint_child);
	// wait pid1 --> exit code irrelevant
	waitpid(pid1, &status, 0);
	// wait pid2
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	set_sigaction(SIGINT, handle_sigint_interactive);
	return (exit_status);
}
