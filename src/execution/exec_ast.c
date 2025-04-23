
#include "minishell.h"

void	exec_ast(t_ast *ast)
{	
	if (ast->ttype == TT_CMD)
		get_shell()->exit_code = exec_cmd(ast);
	else if (ast->ttype == TT_PIPE)
		get_shell()->exit_code = exec_pipe(ast);
}
