
#include "minishell.h"

char	**ast_dup_tokens(char **tokens)
{
	int		i;
	char	**copy;

	i = 0;
	while (tokens[i])
		i++;
	copy = (char **)malloc((i + 1) * sizeof(*copy));
	if (!copy)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		copy[i] = ft_strdup(tokens[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
