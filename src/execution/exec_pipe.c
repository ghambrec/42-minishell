
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
		dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
		close_pipe(pipe_fd);
		exec_ast(ast->left);
		exit(50001);
	}

	// pid2 erstellen
	pid2 = fork();
	if (pid2 == -1)
	{
		close_pipe(pipe_fd);
		perror("Error opening child-process");
		return (errno);
	}
	if (pid2 == 0) // sind im child process
	{
		dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
		close_pipe(pipe_fd);
		exec_ast(ast->right);
		exit(5002);
	}
	close_pipe(pipe_fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}
