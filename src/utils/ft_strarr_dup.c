
#include "minishell.h"

char	**ft_strarr_dup(char **arr)
{
	int		i;
	char	**copy;

	i = 0;
	while (arr[i])
		i++;
	copy = (char **)malloc((i + 1) * sizeof(*copy));
	if (!copy)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		copy[i] = ft_strdup(arr[i]);
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
