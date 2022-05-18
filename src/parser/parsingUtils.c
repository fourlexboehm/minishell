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
	cmd->pipe_in = new_pipe[0];
	(cmd - 1)->pipe_out = new_pipe[1];
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
		cmd->pipe_in = STDIN_FILENO;
		cmd->pipe_out = STDOUT_FILENO;
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

void make_cmd(t_token *tkn_lst_array, t_cmd *cmd)
{
	tkn_lst_array = make_argv(tkn_lst_array, cmd);
	cmd->name = cmd->argv[0];
//	if (!tkn_lst_array) I have no idea why this was here
//		return ;
	make_redirs(tkn_lst_array, cmd);
}
