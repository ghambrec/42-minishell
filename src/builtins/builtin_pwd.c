

#include "minishell.h"

void	builtin_pwd(void)
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
		get_shell()->exit_code = errno;
	}
}
