/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeRedirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:28:41 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:28:45 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//joins the PWD to value if it isn't a fully qualified path
static char	*redir_out(int *out, int type, char *value)
{
	char	*file;
	int		mode;

	if (type == t_redir_to_f)
		mode = O_APPEND;
	else
		mode = O_TRUNC;
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
		return (NULL);
	}
	return (value);
}

static char	*redir_in(int *in, int type, char *value)
{
	char	*file;

	if (type == t_redir_from_f)
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

void	make_redirs(t_token *tkn_lst, t_cmd *cmd)
{
	cmd->redir_in = 0;
	cmd->redir_out = 1;
	while (tkn_lst && tkn_lst->type != t_pipe)
	{
		if (tkn_lst->type == t_redir_from_f || tkn_lst->type == t_redir_from_h)
		{
			tkn_lst->next->value = redir_in(&cmd->redir_in,
					tkn_lst->type, tkn_lst->next->value);
			if (tkn_lst->next)
				tkn_lst = tkn_lst->next->next;
		}
		else if (tkn_lst->type == t_redir_to_f || tkn_lst->type == t_append_rd)
		{
			tkn_lst->next->value = redir_out(&cmd->redir_out,
					tkn_lst->type, tkn_lst->next->value);
			if (tkn_lst->next)
				tkn_lst = tkn_lst->next->next;
		}
		else
			safe_exit(printf("redirect handler encounter unexpected tkn_type,"
					" check tokenizer"));
	}
	cmd->pipe_in = 0;
	cmd->pipe_out = 1;
}
