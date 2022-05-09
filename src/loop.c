#include "../inc/minishell.h"

static void freecmd(t_cmd cmd)
{
	free2d_array((void **)cmd.argv);
	cmd.argv = NULL;
	cmd.name = NULL;
}

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
static char	*rl_get(void)
{
	static char const	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free((char *)line_read);
		line_read = (char *) NULL;
	}
	line_read = readline(">>>");
	if (*line_read)
		add_history(line_read);
	return ((char *)line_read);
}

static int iterate_cmds(t_pathlist *path, t_cmd *cmds, bool *notexit)
{
	int	i;

	i = 0;
	while(cmds[i].name)
	{
		(*notexit) = ft_strncmp("exit", cmds[i].name, 5);
		if (!*notexit)
			return (i);
		executor(path->path, &cmds[i]);
		freecmd(cmds[i++]);
	}
	free(cmds);
	cmds = NULL;
	return (0);
}

//TODO implement
void	loop_shell(t_pathlist *path)
{
	t_lex	lex_data;
	t_cmd	*cmds;
	bool	notexit;
	int		i;

	i = 0;
	notexit = true;
	while (notexit)
	{
		lex_data.token_list = lex(rl_get(), &lex_data);
		cmds = parse(&lex_data.token_list);
		if (cmds && cmds->name)
			i = iterate_cmds(path, cmds, &notexit);
	}
	while (cmds && cmds[i].argv)
		freecmd(cmds[i++]);
	free(cmds);
}

