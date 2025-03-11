
#include "minishell.h"

void	free_ast_redirections(t_redirection *redirect)
{
	t_redirection *tmp;

	while (redirect)
	{
		tmp = redirect;
		free(redirect->filename);
		redirect->filename = NULL;
		redirect = redirect->next;
		free(tmp);
	}
}

void	free_ast_recursive(t_ast *ast)
{
	if (!ast)
		return;
	free_split(ast->cmd);
	ast->cmd = NULL;
	if (ast->redirect)
		free_ast_redirections(ast->redirect);
	free_ast_recursive(ast->left);
	free_ast_recursive(ast->right);
}

void	free_ast(t_ast *ast)
{
	free_ast_recursive(ast);
	free(ast);
}
