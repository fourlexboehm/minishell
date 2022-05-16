#include "../../inc/minishell.h"

t_token	*lex(char const *line, t_lex *lex_data)
{
	t_token *token;
	t_token	*tkn_lst;

	lex_data->line = line;
	lex_data->i = 0;
	tkn_lst = NULL;
	skip_whitespace(lex_data);
	while (line[lex_data->i])
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
	}
	return(tkn_lst);
}
