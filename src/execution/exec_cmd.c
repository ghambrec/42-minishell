/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:13:19 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 18:13:20 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child_process(t_ast *ast)
{
	int	exit_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ast->ttype == TT_CMD)
	{
		exit_code = open_redirections(ast->redirect);
		if (exit_code != 0)
			exit(exit_code);
		execute_command(ast->cmd);
	}
	return (0);
}

static int	exec_parent_process(pid_t pid, int *status)
{
	int	exit_code;

	exit_code = 0;
	set_sigaction(SIGINT, handle_sigint_child);
	waitpid(pid, status, 0);
	set_sigaction(SIGINT, handle_sigint_interactive);
	if (WIFEXITED(*status))
		exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		exit_code = 128 + WTERMSIG(*status);
	return (exit_code);
}

int	exec_cmd(t_ast *ast)
{
	pid_t	pid;
	int		exit_code;
	int		status;

	exit_code = 0;
	if (ast->cmd && check_builtin(ast->cmd) == true)
		return (exec_builtin(ast));
	pid = fork();
	if (pid == -1)
		return (perror("Error creating child"), errno);
	if (pid == 0)
		return (exec_child_process(ast));
	else
		return (exec_parent_process(pid, &status));
}