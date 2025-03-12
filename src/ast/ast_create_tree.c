
#include "minishell.h"

t_ast	*ast_create_tree(t_tokens **tokens)
{
	t_ast		*tree;
	t_tokens	*backup;

	backup = *tokens;
	tree = ast_parse_logical_operator(tokens);
	*tokens = backup;
	return (tree);
}
