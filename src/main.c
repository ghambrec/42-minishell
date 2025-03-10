
#include "minishell.h"



// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(void)
{
	char		*input;
	t_tokens	*tokens;
	t_ast		*ast;
	// atexit(leaks);
	while (1)
	{
		tokens = NULL;
		input = readline("\033[0;36m> \033[0m");
		if (!input) // STRG-D closes the shell
			break ;
		if (input[0])
		{
			if (no_open_quotes(input) == -1)
				continue ;
			create_command_list(input, &tokens);
			ast = ast_create_tree(&tokens);
			free_tokens(tokens);
			if (PRINT_TREE == 1)
				ast_print(ast);

		}


		add_history(input);
		free(input);
	}
	clear_history();
	return (EXIT_SUCCESS);
}
