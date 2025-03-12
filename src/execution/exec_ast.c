/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:15:20 by ghambrec          #+#    #+#             */
/*   Updated: 2025/03/12 13:34:44 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ast(t_ast *ast)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ast->ttype == TT_CMD)
		{
			execute_command(ast->cmd);
		}	
	}
	else
	{
		waitpid(pid, NULL, 0);

	}
}