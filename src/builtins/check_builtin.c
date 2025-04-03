
#include "minishell.h"

bool	check_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "pwd") == 0) 
		return (true);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (true);
	else
		return (false);
}
