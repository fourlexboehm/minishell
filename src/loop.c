#include "../inc/minishell.h"

static void freecmd(t_cmd cmd)
{
	free2d_array((void **)cmd.args);
	cmd.args = NULL;
	cmd.name = NULL;
}

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
	t_lex	lex_data;
	char	*line;

	i = 0;
	while (true)
	{
		line = rl_get();
		lex_data.token_list = lex(line, &lex_data);
		if (path->cmd->name)
		{
			while(path->cmd[i].args)
			{
				if (!ft_strncmp("exit", path->cmd[i].name, 5))
					goto exit ;
				run_if_valid_cmd(path, 0);
				freecmd(path->cmd[i++]);
			}
			i = 0;
			free(path->cmd);
			path->cmd = NULL;
		}

	}
	exit:
	while (path->cmd[i].args)
		freecmd(path->cmd[i++]);
	free(path->cmd);
}