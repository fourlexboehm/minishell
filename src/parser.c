
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
/*t_cmd	*lex(char *line)
{
	t_cmd *cmds;
	int numcmds;
	int i;
	char **cmdvec;
	char **currcmdvec;

	cmdvec = ft_split(line, '|');
	numcmds = n_str_in_vec(cmdvec);
	cmds = malloc(sizeof(t_cmd) * (numcmds + 1));
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
	free2d_array((void **)cmdvec);
	return (cmds);
} */
t_token	*lex(char *line, t_lex *lex_data)
{
	t_token *token;
	t_token	*tkn_lst;

	//line = lex_data->line;
	lex_data->i = 0;
	int	j = 0;
	tkn_lst = NULL;

	skip_whitespace(lex_data);
	while (line[lex_data->i] != '\0')
	{
		printf("this is first c %c and line is %s\n", line[j], line);
		token = new_token(&tkn_lst);
		if (line[lex_data->i] == '"' || line[lex_data->i] == '\'')
		{
			printf("into if statement");
			handle_quote(token, lex_data);
		}
		//else
			//printf("Other");
		//printf("token is %s\n", token->value);
	}
	return(tkn_lst);
}