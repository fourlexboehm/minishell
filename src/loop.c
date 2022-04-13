
#include "../inc/minishell.h"


/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char *rl_gets()
{
	static char *line_read = (char *)NULL;
	if (line_read)
	{
		free (line_read);
		line_read = (char *)NULL;
	}
	//TODO thread prompt variable to here??
	line_read = readline(">>>");
	if (*line_read)
		add_history(line_read);
	return(line_read);
}

//TODO implement
void	loop_shell(t_pathlist *path)
{
	int	i;

	i = 0;
	while(true)
	{
		//temporary short circuit until parsers done
		path->cmd[i]->name = rl_gets();
		if (path->cmd)
		{
			if (!ft_strncmp("exit", path->cmd[i]->name, 5))
				break ;
			//only reading the first command
			run_if_cmd(path, 0);
		}
	}
}