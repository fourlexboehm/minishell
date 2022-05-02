
#include "../inc/minishell.h"

static int	n_cmds(t_token *token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == command)
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

static void expandlst(t_token *lst)
{
	while (lst)
	{
		if (lst->type == single_quotes)
		{
			lst = lst->next;
			while(lst && lst->type != single_quotes)
				lst = lst->next;
		}
		else if (lst->type == command || lst->type == double_quotes)
		{
			expand_variables(&lst->value);
		}
		if (lst)
			lst = lst->next;
	}
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

//generate the token list for each command
t_cmd *make_cmd_lst(t_token **tkn_lst_array)
{
	int		numcmds;
	int		i;
	t_cmd	*cmds;
//	int j;
	i = 0;
	while (tkn_lst_array)
	{
		numcmds = n_cmds(tkn_lst_array[i]);
		cmds = malloc(sizeof(t_cmd) * (numcmds + 1));
		while (tkn_lst_array[i])
		{
			if (tkn_lst_array[i]->type == 0)
				cmds[i].name = tkn_lst_array[i]->value;
			tkn_lst_array[i] = tkn_lst_array[i]->next;
			i++;
		}
		cmds[i].args = NULL;
		cmds[i].name = NULL;
	}
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