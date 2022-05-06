#include "../inc/minishell.h"

void    redir_out(t_cmd *cmd, int type, char *value)
{
    if (type ==  2) //type 2 being '>'
    {
        cmd->out = open(value, O_CREAT | O_RDWR | O_APPEND, 0777);
        if (cmd->out == -1)
            printf("ERROR MSG\n");
        else
        {
            dup2(cmd->out, 1);
            close(cmd->out);
        }
    }
    if (type == 1) // type 1 being '>>' 
    {
        cmd->out = open(value, O_CREAT | O_RDWR | O_TRUNC, 0777);
        if (cmd->out == -1)
            printf("ERROR MSG\n");
        else
        {
            dup2(cmd->out, 1);
            close(cmd->out);
        }
    }
}

void    redir_in(t_cmd *cmd, char *value)
{
        cmd->in = open(value, O_RDONLY | O_CREAT);
        if (cmd->in == -1)
            printf("ERROR MSG\n");
        else
        {
            dup2(cmd->in, 0);
            close(cmd->in);
        }
}

///heredoc function....
///still trying to get my head around how this is going to work..
//https://github.com/gallegoloco/minishell/blob/main/srcs/redirection/heredoc.c
//https://github.com/jmartini89/42_minishell/tree/master/src/exec/redirections
//https://github.com/lskywalker/minishell/blob/master/src/parser/parser_here_doc.c
//https://github.com/Jachokoreto/minishell/blob/main/src/exe_heredoc.c  --doesnt fork
