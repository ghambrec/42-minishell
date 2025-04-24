#include "minishell.h"

char	**ft_sort_2d_strings(char **strings2d)
{
	int		len;
	int		i;
	int		j;
	char	*temp;

	len = 0;
	while (strings2d[len])
		len++;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(strings2d[j], strings2d[j + 1]) > 0)
			{
				temp = strings2d[j];
				strings2d[j] = strings2d[j + 1];
				strings2d[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (strings2d);
}
