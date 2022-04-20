#include "../inc/minishell.h"

static void	quit_process(int signal)
{
	(void)signal;
	//TODO error handling
	ft_printf("Quit (core dumped)\n");
}

void	interrupt_process(int signal)
{
	(void)signal;
// TODO error handling
	write(1, "\n", 1);
}

void	define_exec_signals(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}
