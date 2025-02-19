

#include "minishell.h"

t_buildins	check_builtin(char *program)
{
	if (ft_strcmp(program, "echo") == 0)
		return (BIN_ECHO);
	if (ft_strcmp(program, "cd") == 0)
		return (BIN_CD);
	if (ft_strcmp(program, "pwd") == 0)
		return (BIN_PWD);
	if (ft_strcmp(program, "export") == 0)
		return (BIN_EXPORT);
	if (ft_strcmp(program, "unset") == 0)
		return (BIN_UNSET);
	if (ft_strcmp(program, "env") == 0)
		return (BIN_ENV);
	if (ft_strcmp(program, "exit") == 0)
		return (BIN_EXIT);
	return (NO_BIN);
}
