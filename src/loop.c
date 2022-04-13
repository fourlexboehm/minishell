#include "../inc/minishell.h"

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
//TODO thread prompt variable to here??
static char	*rl_get(void)
{
	static char	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
	line_read = readline(">>>");
	if (*line_read)
		add_history(line_read);
	return (line_read);
}

//TODO implement
//currently only reading the first command
void	loop_shell(t_pathlist *path)
{
	int	i;

	i = 0;
	while (true)
	{
		path->cmd = lex(rl_get());
		if (path->cmd)
		{
			if (!ft_strncmp("exit", path->cmd[i].name, 5))
				break ;
			run_if_cmd(path, 0);
		}
	}
}
