
#include "minishell.h"



// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(void)
{
	char		*input;
	t_tokens	*tokens;
	// t_ast		*ast;
	// atexit(leaks);
	while (1)
	{
		tokens = NULL;
		input = readline("\033[0;36m> \033[0m");
		if (!input) // STRG-D closes the shell
			break ;
		add_history(input);
		if (input[0])
		{
			if (parsing_errors(input))
			{
				free(input);
				continue ;
			}
			create_command_list(input, &tokens);
			// ast = ast_create_tree(&tokens);
			free_tokens(tokens);
			// tokens = NULL;
			// if (PRINT_TREE == 1)
			// 	ast_print(ast);
			// exec_ast(ast); // TODO: exec part
			// free_ast(ast);
			}
		free(input);
		// leaks();
	}
	clear_history();
	return (EXIT_SUCCESS);
}
