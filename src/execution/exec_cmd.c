
# include "minishell.h"

int	exec_cmd(t_ast *ast)
{
	pid_t	pid;
	int		exit_code;

	exit_code = 0;

	if (check_builtin(ast->cmd) == true)
		return (exec_builtin(ast));

	pid = fork();
	if (pid == 0)
	{
		if (ast->ttype == TT_CMD)
		{
			exit_code = open_redirections(ast->redirect);
			if (exit_code != 0)
				exit(exit_code);
			execute_command(ast->cmd);
		}	
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (exit_code);
}