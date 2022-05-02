
#include "../inc/minishell.h"

static int	n_tokens(t_token **token)
{
	int	i;
	t_token *tmp;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

//TODO work in progress
t_cmd	*parse(t_token **lst)
{
	t_cmd *cmds;
	int numcmds;
	int i;
	t_token *tkn_lst = *lst;

	numcmds = n_tokens(lst);
	cmds = malloc(sizeof(t_cmd) * (numcmds + 1));
	i = 0;
	while (tkn_lst)
	{
		if (tkn_lst->type == 0)
			cmds[i].name = tkn_lst->value;
		tkn_lst = tkn_lst->next;
		i++;
	}
	cmds[i].args = NULL;
	cmds[i].name = NULL;
	return (cmds);
}