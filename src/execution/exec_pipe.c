/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:39:01 by ghambrec          #+#    #+#             */
/*   Updated: 2025/04/23 14:49:41 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[PIPE_WRITE]);
	close(pipe_fd[PIPE_READ]);
}

static void	leaf_execution(int direction, int *pipe_fd, t_ast *node)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (direction == PIPE_READ)
		dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
	else if (direction == PIPE_WRITE)
		dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
	close_pipe(pipe_fd);
	exit(exec_ast(node));
}

static int	check_child_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

int	exec_pipe(t_ast *ast)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;
	int	exit_code;
	int	status;

	if (pipe(pipe_fd) == -1)
		return (perror("Error opening pipe"), errno);
	pid1 = fork();
	if (pid1 == -1)
		return (close_pipe(pipe_fd), perror("fork-error"), errno);
	if (pid1 == 0)
		leaf_execution(PIPE_WRITE, pipe_fd, ast->left);
	pid2 = fork();
	if (pid2 == -1)
		return (close_pipe(pipe_fd), perror("fer"), kill(pid1, SIGTERM), errno);
	if (pid2 == 0)
		leaf_execution(PIPE_READ, pipe_fd, ast->right);
	close_pipe(pipe_fd);
	set_sigaction(SIGINT, handle_sigint_child);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	exit_code = check_child_status(status);
	return (set_sigaction(SIGINT, handle_sigint_interactive), exit_code);
}
