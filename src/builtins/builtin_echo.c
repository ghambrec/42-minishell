

#include "minishell.h"

void	builtin_echo(char **cmd)
{
	int		i;
	bool	option_n;

	i = 1;
	option_n = false;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		i = 2;
		option_n = true;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (option_n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
