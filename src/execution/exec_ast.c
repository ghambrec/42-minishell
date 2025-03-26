
#include "minishell.h"

void	exec_ast(t_ast *ast)
{	
	if (ast->ttype == TT_CMD)
		get_shell()->exit_code = exec_cmd(ast);
	// else if (ast->ttype == TT_PIPE)
	// 	get_shell()->exit_code = exec_pipe(ast);


	// TEMPORARY EXIT-CODES:
	// 9000 -> builtin
	// 9001 -> normal command
	printf("%s%sEXIT-CODE: %i%s\n",PURPLE, ITALIC, get_shell()->exit_code, NC);
}
