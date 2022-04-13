
#include "../inc/minishell.h"

int	n_str_in_vec(char **vec)
{
	int	i;

	i = 0;
	while (vec[i++])
		;
	return (i - 1);
}

//very simply temporary lexer, only splits pipes into separate commands,
//doesn't handle quotes or redirects
t_cmd	*lex(char *line)
{
	t_cmd	*cmds;
	int		numcmds;
	int		i;
	char	**cmdvec;
	char	**currcmdvec;

	cmdvec = ft_split(line, '|');
	numcmds = n_str_in_vec(cmdvec);
	cmds = malloc(sizeof(t_cmd) * numcmds + 1);
	i = 0;
	while (i < numcmds)
	{
		currcmdvec = ft_split(cmdvec[i], ' ');
		cmds[i].name = currcmdvec[0];
		cmds[i].args = currcmdvec;
		i++;
	}
	cmds[i].args = NULL;
	cmds[i].name = NULL;
	free(cmdvec);
	return (cmds);
}
