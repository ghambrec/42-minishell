
#include "minishell.h"

void	print_token_type(t_token_type type)
{
	if (type == TT_AND)
		printf("AND");
	else if (type == TT_CMD)
		printf("CMD");
	else if (type == TT_HEREDOC)
		printf("HEREDOC");
	else if (type == TT_OR)
		printf("OR");
	else if (type == TT_PIPE)
		printf("PIPE");
	else if (type == TT_RE_APPEND)
		printf("RE_APPEND");
	else if (type == TT_RE_INPUT)
		printf("RE_INPUT");
	else if (type == TT_RE_OUTPUT)
		printf("RE_OUTPUT");
	else
		printf("undefined");
}

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
}

void	ast_print_recursive(t_ast *ast, int depth, char position)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	while (i++ < depth)
		printf("\t");
	if (position != '0')
		printf("%s└─ %s%c: %s", CYAN, GREY, position, NC);
	else
		printf("%s└─ %s", CYAN, NC);
	print_token_type(ast->ttype);
	if (ast->ttype == TT_CMD)
	{
		printf("%s [", ITALIC);
		print_cmd(ast->cmd);
		printf("]%s", NC);
	}
	printf("\n");
	if (ast->left)
		ast_print_recursive(ast->left, depth + 1, 'L');
	if (ast->right)
		ast_print_recursive(ast->right, depth + 1, 'R');
}

void	ast_print(t_ast *ast)
{
	printf("%sAST%s\n", YELLOW, NC);
	ast_print_recursive(ast, 0, '0');
}
