
#include "../inc/minishell.h"

static int	n_tokens(t_token **token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_token	*lex(char const *line, t_lex *lex_data)
{
	t_token *token;
	t_token	*tkn_lst;
	//t_token *curr;

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
		//printf("token is %s and lineC is %c\n", token->value, lex_data->line[lex_data->i]);
	}
//	curr = tkn_lst;
//	if(curr)
//	{
//		while(curr->next)
//		{
//			printf("val is %s\n", curr->value);
//			curr = curr->next;
//		}
//	}
	return(tkn_lst);
}

//TODO work in progress
t_cmd	*parse(t_token **lst)
{
	t_cmd *cmds;
	int numcmds;
	int i;
	t_token *tkn_lst = *lst;

	numcmds = n_tokens(lst);
	cmds = malloc(sizeof(t_cmd) * (numcmds + 1));
	i = 0;
	while (tkn_lst)
	{
		if (tkn_lst->type == 0)
			cmds[i].name = tkn_lst->value;
		tkn_lst = tkn_lst->next;
		i++;
	}
	cmds[i].args = NULL;
	cmds[i].name = NULL;
	return (cmds);
}