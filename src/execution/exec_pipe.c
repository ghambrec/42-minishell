
#include "minishell.h"

// int	exec_pipe(t_ast *ast)
// {
// 	int	pipe_fd[2];
// 	int	pid1;
// 	int	pid2;

// 	// pipe erstellen
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("Error opening pipe");
// 		return (errno);
// 	}
// 	// pid1 erstellen
// 	pid1 = fork();
// 	if (pid1 == -1)
// 	{
// 		close(pipe_fd[PIPE_WRITE]);
// 		close(pipe_fd[PIPE_READ]);
// 		perror("Error opening child-process");
// 		return (errno);
// 	}
// 	if (pid1 == 0) // sind im child process
// 	{
// 		dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
// 		close(pipe_fd[PIPE_WRITE]);
// 		close(pipe_fd[PIPE_READ]);
// 		exec_ast(ast->left);
// 		exit(50001);
// 	}

// 	// pid2 erstellen
// 	pid2 = fork();
// 	if (pid2 == -1)
// 	{
// 		close(pipe_fd[PIPE_WRITE]);
// 		close(pipe_fd[PIPE_READ]);
// 		perror("Error opening child-process");
// 		return (errno);
// 	}
// 	if (pid2 == 0) // sind im child process
// 	{
// 		dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
// 		close(pipe_fd[PIPE_WRITE]);
// 		close(pipe_fd[PIPE_READ]);
// 		exec_ast(ast->right);
// 		exit(5002);
// 	}
// 	close(pipe_fd[PIPE_WRITE]);
// 	close(pipe_fd[PIPE_READ]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (EXIT_SUCCESS);
// }
