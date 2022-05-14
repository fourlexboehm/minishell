#include "../../inc/minishell.h"

static int	n_redirs_in(t_token *token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == t_redir_from_here_st || tmp->type == t_redir_from_file)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static int	n_redirs_out(t_token *token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == t_redir_to_file || tmp->type ==  t_append_rd)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void    redir_out(int *out, int type, char *value)
{
	char *file;

	//joins the PWD to value if it isn't a fully qualified path
	if (*value != '/')
	{
		file = getfile(search("PWD").data, value);
		free(value);
		value = file;
	}
	if (type ==  t_redir_to_file) //type 2 being '>'
	{

		*out = open(value, O_CREAT | O_RDWR | O_APPEND, 0777);
		if (*out == -1)
		{
			printf("ERROR MSG\n");
			return ;
		}
	}
	//if (type == t_append_rd) // type 1 being '>>'
	{
		*out = open(value, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (*out == -1)
			printf("ERROR MSG\n");
		else
		{
			dup2(*out, 1);
			close(*out);
		}
	}
}

static void    redir_in(int *in, int type, char *value)
{
	char *file;

	if (*value != '/')
	{
		file = getfile(search("PWD").data, value);
		free(value);
		value = file;
	}
	if (type == t_redir_from_file)
	{
		*in = open(value, O_RDONLY | O_CREAT);
		if (*in == -1)
			printf("ERROR MSG\n");
	}
//	if (type == t_redir_from_here_st)
//		heredoc(value, )
}

void make_redirs(t_token *tkn_lst, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd->redir_in = ft_calloc(n_redirs_in(tkn_lst) + 1, sizeof (int));
	cmd->redir_out = ft_calloc(n_redirs_out(tkn_lst) + 1, sizeof (int));
	while (tkn_lst && tkn_lst->type != t_pipe)
	{
		if (tkn_lst->type == t_redir_from_file || tkn_lst->type == t_redir_from_here_st)
		{
			redir_in(cmd->redir_in + i++, tkn_lst->type, tkn_lst->next->value);
			if (tkn_lst->next)
				tkn_lst = tkn_lst->next->next;
		}
		else if (tkn_lst->type == t_redir_to_file || tkn_lst->type == t_append_rd)
		{
			redir_out(cmd->redir_out + j++, tkn_lst->type, tkn_lst->next->value);
			if (tkn_lst->next)
				tkn_lst = tkn_lst->next->next;
		}
	}
}

///heredoc function....
///still trying to get my head around how this is going to work..
//https://github.com/gallegoloco/minishell/blob/main/srcs/redirection/heredoc.c
//https://github.com/jmartini89/42_minishell/tree/master/src/exec/redirections
//https://github.com/lskywalker/minishell/blob/master/src/parser/parser_here_doc.c
//https://github.com/Jachokoreto/minishell/blob/main/src/exe_heredoc.c  --doesnt fork
