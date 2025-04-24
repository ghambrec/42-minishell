
#include "minishell.h"

void	handle_input(char *input)
{
	t_tokens	*tokens;
	t_ast		*ast;

	tokens = NULL;
	if (parsing_errors(input))
	{
		get_shell()->exit_code = 2;
		return ;
	}
	if (create_command_list(input, &tokens) == EXIT_FAILURE)
	{
		get_shell()->exit_code = 2;
		return ;
	}
	ast = ast_create_tree(&tokens);
	free_tokens(tokens);
	tokens = NULL;
	exec_ast(ast);
	free_ast(ast);
}
