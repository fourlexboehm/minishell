#include "../../inc/minishell.h"

static char	*redir_out(int *out, int type, char *value)
{
	char *file;
	int mode;

	if (type == t_redir_to_file)
		mode = O_APPEND;
	else
		mode = O_TRUNC;
	//joins the PWD to value if it isn't a fully qualified path
	if (*value != '/')
	{
		file = getfile(search("PWD").data, value);
		free(value);
		value = file;
	}
	*out = open(value, O_CREAT | O_RDWR | mode, 0777);
	if (*out == -1)
	{
		printf("File could not be opened\n");
		return(NULL);
	}
	dup2(*out, 1);
	close(*out);
	return (value);
}

static char *redir_in(int *in, int type, char *value)
{
	char *file;

	if (type == t_redir_from_file)
	{
		if (*value != '/')
		{
			file = getfile(search("PWD").data, value);
			free(value);
			value = file;
		}
		*in = open(value, O_RDONLY | O_CREAT);
		if (*in == -1)
			printf("File could not be opened\n");
	}
	else
	{
		heredoc(value);
		*in = open("/tmp/tmp_file", O_RDONLY);
	}
	return (value);
}

void make_redirs(t_token *tkn_lst, t_cmd *cmd)
{
	cmd->redir_in = 0;
	cmd->redir_out = 1;
	while (tkn_lst && tkn_lst->type != t_pipe)
	{
		if (tkn_lst->type == t_redir_from_file || tkn_lst->type == t_redir_from_here_st)
		{
			tkn_lst->next->value = redir_in(&cmd->redir_in, tkn_lst->type, tkn_lst->next->value);
			if (tkn_lst->next)
				tkn_lst = tkn_lst->next->next;
		}
		else if (tkn_lst->type == t_redir_to_file || tkn_lst->type == t_append_rd)
		{
			tkn_lst->next->value = redir_out(&cmd->redir_out, tkn_lst->type, tkn_lst->next->value);
			if (tkn_lst->next)
				tkn_lst = tkn_lst->next->next;
		}
		else
			exit(printf("redirect handler encounter unexpected tkn_type, check tokenizer")); //TODO remove exit
	}
}