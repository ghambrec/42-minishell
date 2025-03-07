
#include "minishell.h"

t_ast	*ast_create_tree(t_tokens **tokens)
{
	return (ast_parse_logical_operator(tokens));
}
