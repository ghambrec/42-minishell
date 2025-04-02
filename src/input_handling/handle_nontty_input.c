
#include "minishell.h"

void	handle_nontty_input()
{
	char	*input;
	char	*new_line;
	char	*tmp;

	tmp = ft_strdup("");
	new_line = get_next_line(STDIN_FILENO);
	while (new_line)
	{
		input = ft_strjoin(tmp, new_line);
		free(tmp);
		free(new_line);
		new_line = get_next_line(STDIN_FILENO);
		tmp = input;
	}
	free(new_line);
	handle_input(input);
}
