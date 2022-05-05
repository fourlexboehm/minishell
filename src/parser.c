
#include "../inc/minishell.h"

static int	n_args(t_token *token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == t_command || tmp->type == t_single_quotes
		|| tmp->type == t_double_quotes )
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static int	n_pipes(t_token **token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		if (tmp->type == t_pipe)
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
	cmd--;
	cmd->out = new_pipe[1];
}

static bool	check_filename_after_redir(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->type == t_redir_to_file || token->type == t_redir_from_file
		|| token->type == t_redir_from_here_st)
			if (!next || !(next->type == t_command || next->type == t_double_quotes
			|| next->type == t_single_quotes))
				return (false);
		token = next;
	}
	return (true);
}

//splits the token list into an array of token lists
static t_token **split_tkn_lsts(t_token **lst)
{
	t_token **tkn_lst_array;
	t_token *tmp;
	int i;
	int		numpipes;

	numpipes = n_pipes(lst);
	tkn_lst_array = malloc(sizeof(char *) * (numpipes + 2));
	tkn_lst_array[numpipes + 2] = NULL;
	i = 0;
	tkn_lst_array[i] = *lst;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == t_pipe)
		{
			(*lst)->next = NULL;
			*lst = tmp;
			tkn_lst_array[++i] = *lst;
		}
		*lst = tmp;
		tmp = (*lst)->next;
	}
	return (tkn_lst_array);
}

//generate
//TODO add redirect handling
static void make_cmd(t_token *tkn_lst, t_cmd *cmd)
{
	int i;

	if (tkn_lst->type == t_pipe)
	{
		make_pipe(cmd);
		tkn_lst = tkn_lst->next;
	}
	else
	{
		cmd->in = 0;
		cmd->out = 0;
	}
	cmd->argc = n_args(tkn_lst);
	cmd->argv = ft_calloc(cmd->argc + 1, sizeof (char *));
	i = 0;
	while(i < cmd->argc)
	{
		cmd->argv[i++] = ft_strdup(tkn_lst->value);
		tkn_lst = tkn_lst->next;
	}
	cmd->name = cmd->argv[0];
	if (! tkn_lst)
		return ;
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
		//open(tkn_lst->value, O_CREAT);
	}
	if (tkn_lst->type == t_append_rd)
	{
		tkn_lst = tkn_lst->next;
		redir_out(cmd, 2, tkn_lst->value);
	}
}
//generate the token list for each t_command
static t_cmd *make_cmd_lst(t_token **tkn_lst_array)
{
	int		numcmds;
	int		i;
	t_cmd	*cmds;

	numcmds = n_pipes(tkn_lst_array) + 1;
	cmds = malloc(sizeof(t_cmd) * (numcmds + 1));
	i = -1;
	cmds[0].in = dup(0);
	cmds[numcmds - 1].out = dup(1);
	while (++i < numcmds)
		make_cmd(tkn_lst_array[i], &cmds[i]);
	cmds[i].argv = NULL;
	cmds[i].name = NULL;
	return cmds;
}

//TODO work in progress
t_cmd	*parse(t_token **lst)
{
	t_cmd *cmds;
	t_token **tkn_lst_array;

	if (!check_filename_after_redir(*lst))
	{
		printf("Nowhere to redirect to");
		return (NULL);
	}
	//handle error
	expandlst(*lst);
	tkn_lst_array = split_tkn_lsts(lst);
	cmds = make_cmd_lst(tkn_lst_array);
	free_tkn_lst(tkn_lst_array);
	return (cmds);
}