
#include "minishell.h"

void	handle_nontty_input()
{
	char	*input;
	char	*new_line;

	new_line = get_next_line(STDIN_FILENO);
	while (new_line)
	{
		input = ft_strtrim(new_line, "\n");
		free(new_line);
		handle_input(input);
		new_line = get_next_line(STDIN_FILENO);
	}
}
