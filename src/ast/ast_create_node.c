
#include "minishell.h"

t_ast	*ast_create_node(t_token_type ttype, char **cmd, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->ttype = ttype;
	new_node->cmd = cmd;
	new_node->redirect = NULL;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}
