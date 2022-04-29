#include "../inc/minishell.h"

int is_whitespace(char c)
{
    if (c == ' ' || c == '\t')
        return(1);
    return(0);
}

void skip_whitespace(t_lex  *lex_data)
{
    while(is_whitespace(lex_data->line[lex_data->i]))
        lex_data->i++;
}

t_token *new_token(t_token **list)
{
    t_token *new;
    t_token *temp;

    new = malloc(sizeof(t_token) * 1);
    new->type = 0;
    new->value = "\0";
    new->next = NULL;
    temp = *list;
    if(temp)
    {
        while(temp->next)
            temp = temp->next;
        temp->next = new;
    }
    else
        *list = new;
    return(new);
}

int find_quote(t_lex *lex_data)
{   
    int     j;
    int     k;
    char    c;

    k = lex_data->i;
    j = 0;
    c = lex_data->line[lex_data->i];
    while (lex_data->line[lex_data->i])
    {
        lex_data->i++;
        if (lex_data->line[lex_data->i] == c) {
            printf("value of k is %i and j is %i c is %c and val is %c\n", k, j, c, lex_data->line[k]);
            return(j); 
        }   
        j++;
    }
    return(-1);
}

void    handle_quote(t_token *token, t_lex *lex_data)
{
    int end_quote;
    int start;
    start = lex_data->i;
    if (lex_data->line[lex_data->i] == '"')
        token->type = 1;
    else
        token->type = 2;
    printf("eq is %i\n", end_quote = find_quote(lex_data));
    if(end_quote == -1)
        printf("Unclosed Quotes\n"); ///Errorrrr 
    else
    {
        token->value = ft_substr(lex_data->line, start + 1, end_quote);
        lex_data->i++;
    }
}