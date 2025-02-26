
#include "minishell.h"

// parse && and ||
t_ast	*ast_parse_logical_operator(t_tokens **tokens)
{
	t_ast			*left;
	t_token_type	ttype;

	left = ast_parse_pipe(tokens);
	while (*tokens && ((*tokens)->token_type == TT_AND || (*tokens)->token_type == TT_OR))
	{
		ttype = (*tokens)->token_type;
		*tokens = (*tokens)->next;
		left = ast_create_node(ttype, NULL, left, ast_parse_pipe(tokens));
	}
	return (left);
}

// parse |
t_ast	*ast_parse_pipe(t_tokens **tokens)
{
	t_ast	*left;

	left = ast_parse_cmd(tokens);
	while (*tokens && (*tokens)->token_type == TT_PIPE)
	{
		*tokens = (*tokens)->next;
		left = ast_create_node(TT_PIPE, NULL, left, ast_parse_cmd(tokens));
	}
	return (left);
}

// parse parenthesis (+ skip the open and close parenthesis)
t_ast	*ast_parse_parenthesis(t_tokens **tokens)
{
	t_ast	*cmd;

	*tokens = (*tokens)->next;
	cmd = ast_parse_logical_operator(tokens);
	*tokens = (*tokens)->next;
	return (cmd);
}

// parse cmd
t_ast	*ast_parse_cmd(t_tokens **tokens)
{
	t_ast	*cmd;

	if (*tokens && (*tokens)->token_type == TT_PARENTESIS_OPEN)
		return (ast_parse_parenthesis(tokens));
	cmd = ast_create_node(TT_CMD, (*tokens)->token, NULL, NULL);
	*tokens = (*tokens)->next;
	return (cmd);
}

t_ast	*ast_create_tree(t_tokens **tokens)
{
	return (ast_parse_logical_operator(tokens));
}

// ls -al | (grep Documents || echo hallo) | xargs > file.txt

// int	main(void)
// {
// 	// t_tokens t8 = {TT_RE_OUTPUT, (char *[]){"> file.txt", NULL}, NULL};
// 	t_tokens t7 = {TT_CMD, (char *[]){"xargs", NULL}, NULL};
// 	t_tokens t6 = {TT_PIPE, NULL, &t7};
// 	t_tokens t5 = {TT_PARENTESIS_CLOSE, NULL, &t6};
// 	t_tokens t4 = {TT_CMD, (char *[]){"echo", "hallo", NULL}, &t5};
// 	t_tokens t3 = {TT_OR, NULL, &t4};
// 	t_tokens t2 = {TT_CMD, (char *[]){"grep", "Documents", NULL}, &t3};
// 	t_tokens t1 = {TT_PARENTESIS_OPEN, NULL, &t2};
// 	t_tokens t0 = {TT_PIPE, NULL, &t1};
// 	t_tokens t_1 = {TT_CMD, (char *[]){"ls", "-al", NULL}, &t0};

// 	t_tokens *tokens = &t_1;

// 	t_ast *ast = ast_create_tree(&tokens);
//     ast_print(ast);
//     return 0;
// }
