
#include "minishell.h"

t_redirection *ast_create_redirection(t_token_type ttype, int fd, char *filename)
{
	t_redirection	*new_redirection;

	new_redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_redirection)
	{
		// TODO: wie malloc fehler im parsing handeln?
		return (NULL);
	}
	new_redirection->ttype = ttype;
	new_redirection->fd = fd;
	new_redirection->filename = ft_strdup(filename);
	new_redirection->next = NULL;
	return (new_redirection);
}

// if token[0][0] is a number then get the fd for the redirection, else set 1024 because max open is 1024
void	ast_add_redirection(t_ast *ast, t_token_type ttype, char **token)
{
	int				fd;
	t_redirection	*tmp;

	fd = 1024;
	if (ft_isdigit(token[0][0]))
		fd = ft_atoi(token[0]);
	if (!ast->redirect)
		ast->redirect = ast_create_redirection(ttype, fd, token[1]);
	else
	{
		tmp = ast->redirect;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ast_create_redirection(ttype, fd, token[1]);
	}
}
