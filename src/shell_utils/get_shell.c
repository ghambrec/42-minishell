

#include "minishell.h"

t_shell *get_shell(void)
{
	static t_shell sh;

	return (&sh);
}
