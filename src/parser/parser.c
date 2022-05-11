
#include "../../inc/minishell.h"
//
//static void	save_std_fds(int *save_fd)
//{
//	save_fd[0] = dup(STDIN_FILENO);
//	save_fd[1] = dup(STDOUT_FILENO);
//}
//
//static void	restore_std_fds(int *save_fd)
//{
//	dup2(save_fd[0], STDIN_FILENO);
//	close(save_fd[0]);
//	dup2(save_fd[1], STDOUT_FILENO);
//	close(save_fd[1]);
//}
//
//static void	create_pipe(t_token *pipe_token, int *old_pipe_in)
//{
//	int	new_pipe[2];
//
//	dup2(*old_pipe_in, STDIN_FILENO);
//	if (*old_pipe_in != 0)
//		close(*old_pipe_in);
//	if (!pipe_token)
//		return ;
//	pipe(new_pipe);
//	dup2(new_pipe[1], STDOUT_FILENO);
//	close(new_pipe[1]);
//	*old_pipe_in = dup(new_pipe[0]);
//	close(new_pipe[0]);
//}
//
//static bool	check_filename_after_redirect(t_token *token)
//{
//	t_token	*next;
//
//	while (token)
//	{
//		next = token->next;
//		if (token->type == t_redir_from_file || token->type == t_redir_to_file || token->type == t_redir_from_here_st)
//			if (!next || next->type != )
//				return (false);
//		token = next;
//	}
//	return (true);
//}
//
//void	command_parser(t_token *token_lst, t_token *pipe, int *old_pipe_in)
//{
//	int		save_fd[2];
//	char	**cmd;
//
//	save_std_fds(save_fd);
//	create_pipe(pipe, old_pipe_in);
//	restore_std_fds(save_fd);
//}
//
//void	pipe_checker(t_token *head, int *old_pipe_in)
//{
//	t_token	*current;
//
//	current = head;
//	while (current)
//	{
//		if (current->type == t_pipe)
//		{
//			command_parser(head, current, old_pipe_in);
//			head = current->next;
//			pipe_checker(head, old_pipe_in);
//			break ;
//		}
//		current = current->next;
//	}
//	if (!current)
//		command_parser(head, current, old_pipe_in);
//}
//
//static void	close_last_input_fd(int old_pipe_in)
//{
//	if (old_pipe_in != 0)
//		close(old_pipe_in);
//}
//
//void	parse_and_execute(t_token *token_lst)
//{
//	int	old_pipe_in;
//
//	if (!token_lst)
//		return ;
//	set_first_input_fd(&old_pipe_in);
//	pipe_checker(token_lst, &old_pipe_in);
//	close_last_input_fd(old_pipe_in);
//}

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
	int		numcmds;

	numcmds = n_pipes(lst) + 1;
	tkn_lst_array = malloc(sizeof(char *) * (numcmds + 1));
	tkn_lst_array[numcmds] = NULL;
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