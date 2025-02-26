
#include "minishell.h"

void	free_split(char **split)
{
	char	**orig;

	if (!split)
		return ;
	orig = split;
	while (*split != NULL)
	{
		free(*split);
		*split = NULL;
		split++;
	}
	free(orig);
}
