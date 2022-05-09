#include "../../inc/minishell.h"

void    redir_out(t_cmd *cmd, int type, char *value)
{
	char *file;

	//joins the PWD to value if it isn't a fully qualified path
	if (*value != '/')
	{
		file = getfile(search("PWD").data, value);
		free(value);
		value = file;
	}
	if (type ==  2) //type 2 being '>'
	{

		cmd->out = open(value, O_CREAT | O_RDWR | O_APPEND, 0777);
		if (cmd->out == -1)
		{
			printf("ERROR MSG\n");
			return ;
		}
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
	char *file;

	if (*value != '/')
	{
		file = getfile(search("PWD").data, value);
		free(value);
		value = file;
	}
	cmd->in = open(value, O_RDONLY | O_CREAT);
	if (cmd->in == -1)
		printf("ERROR MSG\n");
	else
	{
		dup2(cmd->in, 0);
		close(cmd->in);
	}
}
