
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (init_shell(argc, argv, envp))
		return (EXIT_FAILURE);

	if (isatty(STDIN_FILENO))
	{
		handle_tty_input();
	}
	else
	{
		handle_nontty_input();
	}
	return (exit_shell(get_shell(), false));
}
