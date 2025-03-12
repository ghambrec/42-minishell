
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

void free_ast(t_ast *ast)
{
	if (!ast)
		return;
	free_ast(ast->left);
	free_ast(ast->right);
	free_split(ast->cmd);
	ast->cmd = NULL;
	if (ast->redirect)
		free_ast_redirections(ast->redirect);
	free(ast);
}
