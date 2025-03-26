
# include "minishell.h"

int	exec_cmd(t_ast *ast)
{
	pid_t	pid;

	if (check_builtin(ast->cmd) == true)
		return (exec_builtin(ast));

	pid = fork();
	if (pid == 0)
	{
		if (ast->ttype == TT_CMD)
		{
			execute_command(ast->cmd);
		}	
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return 0;
}