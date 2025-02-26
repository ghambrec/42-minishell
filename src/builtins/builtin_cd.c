
#include "minishell.h"


// TODO: testcase 	1) cd /
//					2) cd ..


// cd to the given path
// exactly 1 arugument needed (relative or absolute path)
void	builtin_cd(char **cmd)
{
	char	*path;
	char	*slashed_path;
	char	*new_path;

	if (!cmd[1] || cmd[2])
	{
		ft_putendl_fd("Bad usage of cd! Usage: 'cd <parameter>'", STDERR_FILENO);
		return ;
	}
	if (cmd[1][0] == '/')
	{
		if (chdir(cmd[1]) == -1)
		{
			perror("cd");
			get_shell()->exit_code = errno;
		}
	}
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
		{
			perror("cd, error get pwd");
			get_shell()->exit_code = errno;
		}
		slashed_path = ft_strjoin(path, "/");
		new_path = ft_strjoin(slashed_path, cmd[1]);
		if (chdir(new_path) == -1)
		{
			perror("cd");
			get_shell()->exit_code = errno;
		}
		free(path);
		free(slashed_path);
		free(new_path);
	}
}
