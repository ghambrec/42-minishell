
#include "minishell.h"

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens;
		free_split(tokens->token);
		tokens = tokens->next;
		free(tmp);
	}
}
