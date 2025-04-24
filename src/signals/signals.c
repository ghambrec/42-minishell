
#include "minishell.h"

void	handle_sigint_interactive(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_child(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	set_sigaction(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	sigaction(signum, &sa, NULL);
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	set_sigaction(SIGINT, handle_sigint_interactive);
	set_sigaction(SIGQUIT, SIG_IGN);
}
