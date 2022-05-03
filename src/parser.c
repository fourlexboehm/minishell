
#include "../inc/minishell.h"

static int	n_args(t_token *token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == command || tmp->type == single_quotes || tmp->type == double_quotes )
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
		if (tmp->type == pipe)
			i++;
		tmp = tmp->next;
	}
	return (i);
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
	i = 0;
	tkn_lst_array[i] = *lst;
	tmp = *lst;
	while (tmp)
	{

		if (tmp->type == pipe)
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

//TODO add redirect handling
static void make_cmd(t_token *tkn_lst, t_cmd *cmd)
{
	int i;

	cmd->argc = n_args(tkn_lst);
	cmd->args = ft_calloc( cmd->argc + 1, sizeof (char *));
	i = 0;
	while(i < cmd->argc)
	{
		cmd->args[i++] = ft_strdup(tkn_lst->value);
		tkn_lst = tkn_lst->next;
	}
	//cmd->in = dup(0);
	//cmd->out = &tkn_lst->value;
	if (tkn_lst->type == redir_from_file)
	{
		tkn_lst = tkn_lst->next;
		open(tkn_lst->value, O_CREAT);
	}
	if (tkn_lst->type == redir_from_here_st)
	{
		tkn_lst = tkn_lst->next;
		//tkn_lst->value;
	}
	if (tkn_lst->type == redir_to_file)
	{
		tkn_lst = tkn_lst->next;
		open(tkn_lst->value, O_CREAT);
	}

}
//generate the token list for each command
static t_cmd *make_cmd_lst(t_token **tkn_lst_array)
{
	int		numcmds;
	int		i;
	t_cmd	*cmds;
//	int j;
	numcmds = n_pipes(tkn_lst_array) + 1;
	cmds = malloc(sizeof(t_cmd) * (numcmds + 1));
	i = -1;
	while (++i < numcmds)
		make_cmd(tkn_lst_array[i], &cmds[i]);
	cmds[i].args = NULL;
	cmds[i].name = NULL;
	cmds[i].in = NULL;
	cmds[i].out = NULL;
	return cmds;
}

//TODO work in progress
t_cmd	*parse(t_token **lst)
{
	t_token **tkn_lst_array;
	t_cmd *cmds;

	expandlst(*lst);
	tkn_lst_array = split_tkn_lsts(lst);
	cmds = make_cmd_lst(tkn_lst_array);
	return (cmds);

}