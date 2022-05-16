#include "../../inc/minishell.h"

void    smoke_pipes(t_token *token, t_lex *lex_data)
{
    token->type = t_pipe;
    token->value = "|";
    lex_data->i++;
}

void    redir_r(t_token *token, t_lex *lex_data)
{
    if (lex_data->line[lex_data->i] == '>' && lex_data->line[lex_data->i + 1] == '>')
    {
        token->type = t_append_rd; //r_redx2
        token->value = ">>";
        lex_data->i += 2;
    }
    else 
    {
        token->type = t_redir_to_file; //r_redx1
        token->value = ">";
        lex_data->i += 1;
    }
}

void    redir_l(t_token *token, t_lex *lex_data)
{
    if (lex_data->line[lex_data->i] == '<' && lex_data->line[lex_data->i + 1] == '<')
    {
        token->type = t_redir_from_here_st; //l_redx2
        token->value = "<<";
        lex_data->i += 2;
    }
    else 
    {
        token->type = t_redir_from_file; //l_redx1
        token->value = "<";
        lex_data->i += 1;
    }
}

void    handle_rest(t_token *token, t_lex *lex_data)
{
    int start;
    int j;


    start = lex_data->i;
	token->type = t_command;
	j = start;
	while(lex_data->line[j] && !is_whitespace(lex_data->line[j]))
        j++;
    token->value = ft_substr(lex_data->line, start, j - start);
    lex_data->i = j;
}

void free_tkn_lst(t_token **tkn_lst)
{
	void *freeme;

	freeme = tkn_lst;
	while (*tkn_lst)
	{
		while (*tkn_lst)
		{
			if ((*tkn_lst)->type < t_pipe)
				free((*tkn_lst)->value);
			(*tkn_lst)->value = NULL;
			free(*tkn_lst);
			*tkn_lst = (*tkn_lst)->next;
		}
		tkn_lst++;
	}
	free(freeme);
}