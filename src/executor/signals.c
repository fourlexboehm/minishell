#include "../../inc/minishell.h"

static void	quit_process(int signal)
{
	(void)signal;
	//TODO error handling
	printf("Quit (core dumped)\n");
}

void	interrupt_process(int signal)
{
	(void)signal;
// TODO error handling
	write(2, "\n>>>", 4);
}

void	define_exec_signals(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}
