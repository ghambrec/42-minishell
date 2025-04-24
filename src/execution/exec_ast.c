/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:32:24 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:32:28 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_ast(t_ast *ast)
{
	if (ast->ttype == TT_CMD)
		return (get_shell()->exit_code = exec_cmd(ast));
	else if (ast->ttype == TT_PIPE)
		return (get_shell()->exit_code = exec_pipe(ast));
	return (EXIT_FAILURE);
}
