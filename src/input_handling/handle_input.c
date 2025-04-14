
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
	// ft_printlist(tokens);
	// printf("%sCreating AST...%s\n", YELLOW, NC);
	ast = ast_create_tree(&tokens);
	// printf("%sFinished AST...%s\n", YELLOW, NC);
	free_tokens(tokens);
	tokens = NULL;
	if (PRINT_TREE == 1)
		ast_print(ast);
	// printf("%sStarting Execution...%s\n", YELLOW, NC);
	exec_ast(ast);
	free_ast(ast);
	// printf("%sFinished Execution...%s\n", YELLOW, NC);
}
