#include "../../inc/minishell.h"


static int	n_args(t_token *token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp && (tmp->type == t_command || tmp->type == t_single_quotes
		   || tmp->type == t_double_quotes))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	make_pipe(t_cmd *cmd)
{
	int	new_pipe[2];

	pipe(new_pipe);
	cmd->in = new_pipe[0];
	(cmd - 1)->out = new_pipe[1];
}


static void make_redirs(t_token *tkn_lst, t_cmd *cmd)
{
	if (tkn_lst->type == t_redir_from_file)
	{
		tkn_lst = tkn_lst->next;
		redir_in(cmd, tkn_lst->value);
		//open(tkn_lst->value, O_CREAT);
	}
	if (tkn_lst->type == t_redir_from_here_st)
	{
		tkn_lst = tkn_lst->next;
	}
	if (tkn_lst->type == t_redir_to_file)
	{
		tkn_lst = tkn_lst->next;
		redir_out(cmd, 1, tkn_lst->value);
	}
	if (tkn_lst->type == t_append_rd)
	{
		tkn_lst = tkn_lst->next;
		redir_out(cmd, 2, tkn_lst->value);
	}
}


t_token *make_argv(t_token *tkn_lst, t_cmd *cmd)
{
	int i;

	if (tkn_lst && tkn_lst->type == t_pipe)
	{
		make_pipe(cmd);
		tkn_lst = tkn_lst->next;
	}
	else
	{
		cmd->in = STDIN_FILENO;
		cmd->out = STDOUT_FILENO;
	}
	cmd->argc = n_args(tkn_lst);
	cmd->argv = ft_calloc(cmd->argc + 1, sizeof (char *));
	i = 0;
	while(i < cmd->argc)
	{
		cmd->argv[i++] = ft_strdup(tkn_lst->value);
		tkn_lst = tkn_lst->next;
	}
	return tkn_lst;
}

void make_cmd(t_token *tkn_lst, t_cmd *cmd)
{
	tkn_lst = make_argv(tkn_lst, cmd);

	cmd->name = cmd->argv[0];
	if (! tkn_lst)
		return ;
	make_redirs(tkn_lst, cmd);
}

///heredoc function....
///still trying to get my head around how this is going to work..
//https://github.com/gallegoloco/minishell/blob/main/srcs/redirection/heredoc.c
//https://github.com/jmartini89/42_minishell/tree/master/src/exec/redirections
//https://github.com/lskywalker/minishell/blob/master/src/parser/parser_here_doc.c
//https://github.com/Jachokoreto/minishell/blob/main/src/exe_heredoc.c  --doesnt fork
