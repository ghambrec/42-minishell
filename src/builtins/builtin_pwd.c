

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		free(path);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}
