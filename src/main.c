
#include "minishell.h"



// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int ac, char **argv, char **envp)
{
	char		*input;
	t_tokens	*tokens;
	// t_tokens	*tokens_backup_pointer;
	t_ast		*ast;
	// atexit(leaks);
	
	if (input_errors(ac, argv))
		return (1);
	get_shell()->envp = ast_dup_tokens(envp);
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
			// printf("%sCreating Command-List...%s\n", YELLOW, NC);
			create_command_list(input, &tokens);
			// ft_printlist(tokens);
			// tokens_backup_pointer = tokens;
			// printf("%sCreating AST...%s\n", YELLOW, NC);
			ast = ast_create_tree(&tokens);
			// printf("%sFinished AST...%s\n", YELLOW, NC);
			free_tokens(tokens);
			tokens = NULL;
			if (PRINT_TREE == 1)
			ast_print(ast);
			// printf("%sStarting Execution...%s\n", YELLOW, NC);
			exec_ast(ast); // TODO: exec part
			free_ast(ast);
			}
		// free(input); // wird in create_command_list freigegeben
		// leaks();
	}
	clear_history();
	return (EXIT_SUCCESS);
}