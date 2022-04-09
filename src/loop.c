
#include "../inc/minishell.h"


/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char * rl_gets ()
{
	static char *line_read = (char *)NULL;
	/* If the buffer has already been allocated, return the memory
	   to the free pool. */
	if (line_read)
	{
		free (line_read);
		line_read = (char *)NULL;
	}

	/* Get a line from the user. */
	line_read = readline("");

	/* If the line has any text in it, save it on the history. */
	if (line_read && *line_read)
		add_history(line_read);

	return(line_read);
}

//TODO implement
void	loop_shell(t_pathlist *path, t_cmd *cmd)
{
	//readline();
	path->cmd = "export";
	run_if_cmd(path);
	//rl_initialize();
	(void)cmd;
	(void)path;
	while(true)
	{

		readline(">>>");
		usleep(1);
	}
}
