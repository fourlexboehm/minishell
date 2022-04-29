#include "../inc/minishell.h"

static void freecmd(t_cmd cmd)
{
	free2d_array((void **)cmd.args);
	cmd.args = NULL;
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

//TODO implement
//currently only reading the first command
void	loop_shell(t_pathlist *path)
{
	int	i;
	t_lex	lex_data;
	t_cmd	*cmds;

	(void)i; //temporary
	(void)path; //temporary
	i = 0;
	while (true)
	{
		lex_data.token_list = lex(rl_get(), &lex_data);
		cmds = parse(&lex_data.token_list);
		if (cmds->name)
		{
			while(cmds[i].args)
			{
				if (!ft_strncmp("exit", cmds[i].name, 5))
					goto exit ;
				executor(path->path, cmds, i);
				freecmd(cmds[i++]);
			}
			i = 0;
			free(cmds);
			cmds = NULL;
		}
		free_tkn_lst(&lex_data.token_list);
	}
	exit:
	while (cmds[i].args)
		freecmd(cmds[i++]);
	free(cmds);
}