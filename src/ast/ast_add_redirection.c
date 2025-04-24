
#include "minishell.h"

t_redirection	*ast_create_redirection(t_token_type ttype, char *filename)
{
	t_redirection	*new_redirection;

	new_redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_redirection)
		return (NULL);
	new_redirection->ttype = ttype;
	new_redirection->filename = ft_strdup(filename);
	new_redirection->next = NULL;
	return (new_redirection);
}

void	ast_add_redirection(t_ast *ast, t_token_type ttype, char **token)
{
	t_redirection	*tmp;

	if (!ast->redirect)
		ast->redirect = ast_create_redirection(ttype, token[1]);
	else
	{
		tmp = ast->redirect;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ast_create_redirection(ttype, token[1]);
	}
}

bool	is_redirection(t_token_type ttype)
{
	if (ttype == TT_RE_INPUT || ttype == TT_RE_OUTPUT
		|| ttype == TT_RE_APPEND || ttype == TT_HEREDOC)
		return (true);
	return (false);
}
