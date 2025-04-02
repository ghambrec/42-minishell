
#include "minishell.h"

int	init_shell(int argc, char **argv, char **envp)
{
	t_shell *shell;

	(void)argv;
	shell = get_shell();
	if (argc == 1)
	{
		shell->envp = ft_strarr_dup(envp);
		if (!shell->envp)
			return (EXIT_FAILURE);
		shell->exit_code = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
