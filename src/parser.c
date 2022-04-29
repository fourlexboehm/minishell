
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
	t_token *curr;

	lex_data->line = line;
	lex_data->i = 0;
	tkn_lst = NULL;
	skip_whitespace(lex_data);
	while (line[lex_data->i] != '\0')
	{
		skip_whitespace(lex_data);
		token = new_token(&tkn_lst);
		if (line[lex_data->i] == '"' || line[lex_data->i] == '\'')
			handle_quote(token, lex_data);
		else if (line[lex_data->i] == '|')
			smoke_pipes(token, lex_data);
		else if (line[lex_data->i] == '>')
			redir_r(token, lex_data);
		else if (line[lex_data->i] == '<')
			redir_l(token, lex_data);
		else
			handle_rest(token, lex_data);
		//printf("token is %s and lineC is %c\n", token->value, lex_data->line[lex_data->i]);
	}
	curr = tkn_lst;
	if(curr)
	{	
		while(curr->next)
		{
			printf("val is %s\n", curr->value);
			curr = curr->next;
		}	
	}
	return(tkn_lst);
}