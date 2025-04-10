
# include "minishell.h"

int	exec_cmd(t_ast *ast)
{
	pid_t	pid;
	int		exit_code;
	int		status;
	
	exit_code = 0;
	if (ast->cmd && check_builtin(ast->cmd) == true)
		return (exec_builtin(ast));
	pid = fork();
	if (pid == -1)
		return (perror("Error creating child"), errno);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
		set_sigaction(SIGINT, handle_sigint_child);
		waitpid(pid, &status, 0);
		set_sigaction(SIGINT, handle_sigint_interactive);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
	}
	return (exit_code);
}

// TODO: error code handling wenn cmd durch signal abgebrochen wurde (testen sobald wir signals haben ob richtig gesetzt wird)
// sollte funktionieren wegen WIFSIGNALED, aber nochmal testen