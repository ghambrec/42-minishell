

#include "minishell.h"

void	check_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd);
	if (ft_strcmp(cmd[0], "cd") == 0)
		builtin_cd(cmd);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(cmd[0], "export") == 0)
		return ;
	if (ft_strcmp(cmd[0], "unset") == 0)
		return ;
	if (ft_strcmp(cmd[0], "env") == 0)
		return ;
	if (ft_strcmp(cmd[0], "exit") == 0)
		return ;
}
