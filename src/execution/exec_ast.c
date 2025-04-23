
#include "minishell.h"

int	exec_ast(t_ast *ast)
{	
	if (ast->ttype == TT_CMD)
		return(get_shell()->exit_code = exec_cmd(ast));
	else if (ast->ttype == TT_PIPE)
		return(get_shell()->exit_code = exec_pipe(ast));
	return (EXIT_FAILURE);
}
