#include "../inc/minishell.h"

static void freecmd(t_cmd cmd)
{
//	if (cmd.pipe_in != STDIN_FILENO)
//		close(cmd.pipe_in);
//	if (cmd.pipe_out != STDOUT_FILENO)
//		close(cmd.pipe_out);
//	while(cmd.redir_in)
//	{
//		if (*cmd.redir_in != STDIN_FILENO)
//			close(*cmd.redir_in);
//		cmd.redir_in++;
//	}
//	while(cmd.redir_out)
//	{
//		if (*cmd.redir_out != STDOUT_FILENO)
//			close(*cmd.redir_out);
//		cmd.redir_out++;
//	}
	free2d_array((void **)cmd.argv);
	free(cmd.redir_in);
	free(cmd.redir_out);
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
	line_read = readline(">>>");if (*line_read)
		add_history(line_read);
	return ((char *)line_read);
}

static int iterate_cmds(t_pathlist *path, t_cmd *cmds, bool *exit)
{
	int	i;
	int status;

	i = 0;
	while(cmds[i].name)
	{
		*exit = !ft_strncmp("exit", cmds[i].name, 5);
		if (*exit)
			return (i);
		executor(path->path, &cmds[i++]);
	}
	i = 0;
	while(cmds[i].name)
	{
		waitpid(cmds[i].pid, &status, 0);
		if (!WIFEXITED(status))
			printf(" cmd %i returned: %i\n", i, status);
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
	bool	exit;
	int		i;

	i = 0;
	exit = false;
	while (!exit)
	{
		lex_data.token_list = lex(rl_get(), &lex_data);
		cmds = parse(&lex_data.token_list);
		if (cmds && cmds->name)
			i = iterate_cmds(path, cmds, &exit);
	}
	while (cmds && cmds[i].argv)
		freecmd(cmds[i++]);
	free(cmds);
}

