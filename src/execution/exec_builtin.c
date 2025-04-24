/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:33 by ghambrec          #+#    #+#             */
/*   Updated: 2025/04/24 18:30:02 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_current_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd));
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd[0], "export") == 0)
		return (builtin_export(cmd));
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(cmd));
	if (ft_strcmp(cmd[0], "env") == 0)
		return (builtin_env(cmd));
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (builtin_exit(cmd), EXIT_FAILURE);
	else
		return (false);
}

static void	dup_helper(int copy_stdin, int copy_stdout)
{
	dup2(copy_stdin, STDIN_FILENO);
	dup2(copy_stdout, STDOUT_FILENO);
}

int	exec_builtin(t_ast *ast)
{
	int	exit_code;
	int	copy_stdin;
	int	copy_stdout;

	if (ast->redirect)
	{
		copy_stdin = dup(STDIN_FILENO);
		copy_stdout = dup(STDOUT_FILENO);
		exit_code = open_redirections(ast->redirect);
		if (exit_code != 0)
		{
			dup_helper(copy_stdin, copy_stdout);
			return (close(copy_stdin), close(copy_stdout), exit_code);
		}
	}
	exit_code = exec_current_builtin(ast->cmd);
	if (ast->redirect)
	{
		dup_helper(copy_stdin, copy_stdout);
		close(copy_stdin);
		close(copy_stdout);
	}
	if (exit_code > 0)
		exit_code = EXIT_FAILURE;
	return (exit_code);
}
