
#include "minishell.h"

void	handle_tty_input(void)
{
	char	*input;

	while (true)
	{
		input = NULL;
		if (get_shell()->exit_code)
			input = readline("\033[0;31m• \033[0;36m➜\033[0m ");
		else
			input = readline("\033[0;32m• \033[0;36m➜\033[0m ");
		if (!input)
		{
			ft_putendl_fd("\033[A\033[2K\033[0;30m• \033[0;36m➜\033[0m exit", STDOUT_FILENO);
			break ;
		}
		add_history(input);
		handle_input(input);
	}
	clear_history(); // in exit_shell mit rein, falls shell mit befehl exit etc beendet wird
}
