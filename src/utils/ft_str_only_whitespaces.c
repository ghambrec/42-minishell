
#include "minishell.h"

int	ft_str_only_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(" \n\t\n\r", str[i]))
			return (0);
		i++;
	}
	return (1);
}
