
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

// parse cmd
t_ast	*ast_parse_cmd(t_tokens **tokens)
{
	t_ast	*cmd;

	cmd = NULL;
	if (*tokens && is_redirection((*tokens)->token_type))
	{
		cmd = ast_create_node(TT_CMD, NULL, NULL, NULL);
		ast_parse_redirections(cmd, tokens);
	}
	if (*tokens && (*tokens)->token_type == TT_PARENTESIS_OPEN)
		return (ast_parse_parenthesis(tokens));
	if (cmd)
		cmd->cmd = ft_strarr_dup((*tokens)->token);
	else
		cmd = ast_create_node(TT_CMD, ft_strarr_dup((*tokens)->token), NULL, NULL);
	*tokens = (*tokens)->next;
	ast_parse_redirections(cmd, tokens);
	return (cmd);
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

// parse redirections for the command
void	ast_parse_redirections(t_ast *cmd, t_tokens **tokens)
{
	while (*tokens && is_redirection((*tokens)->token_type))
	{
		ast_add_redirection(cmd, (*tokens)->token_type, (*tokens)->token);
		(*tokens) = (*tokens)->next;
	}
}
