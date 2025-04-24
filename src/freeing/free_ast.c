/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:31:31 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 18:04:08 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast_redirections(t_redirection *redirect)
{
	t_redirection	*tmp;

	while (redirect)
	{
		tmp = redirect;
		free(redirect->filename);
		redirect->filename = NULL;
		redirect = redirect->next;
		free(tmp);
	}
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	free_split(ast->cmd);
	ast->cmd = NULL;
	if (ast->redirect)
		free_ast_redirections(ast->redirect);
	free(ast);
}
