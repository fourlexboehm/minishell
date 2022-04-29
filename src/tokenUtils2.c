#include "../inc/minishell.h"

void    smoke_pipes(t_token *token, t_lex *lex_data)
{
    token->type = 3;
    token->value = "|";
    lex_data->i++;
}

void    redir_r(t_token *token, t_lex *lex_data)
{
    if (lex_data->line[lex_data->i] == '>' && lex_data->line[lex_data->i + 1] == '>')
    {
        token->type = 4; //r_redx2
        token->value = ">>";
        lex_data->i += 2;
    }
    else 
    {
        token->type = 5; //r_redx1
        token->value = ">";
        lex_data->i += 1;
    }
}

void    redir_l(t_token *token, t_lex *lex_data)
{
    if (lex_data->line[lex_data->i] == '<' && lex_data->line[lex_data->i + 1] == '<')
    {
        token->type = 6; //l_redx2
        token->value = "<<";
        lex_data->i += 2;
    }
    else 
    {
        token->type = 7; //l_redx1
        token->value = "<";
        lex_data->i += 1;
    }
}

void    handle_rest(t_token *token, t_lex *lex_data)
{
    int start;
    int j;
    
    start = lex_data->i;
	j = start;
	while(lex_data->line[j] && !is_whitespace(lex_data->line[j]))
        j++;
    token->value = ft_substr(lex_data->line, start, j - start);
    lex_data->i = j;
}

void free_tkn_lst(t_token **tkn_lst)
{
    t_token *trash;
    while ((*tkn_lst))
    {
        trash = *tkn_lst;
        *tkn_lst = (*tkn_lst)->next;
        free(trash->value);
        free(trash);
        trash->value = NULL;
        trash = NULL;
    }
}