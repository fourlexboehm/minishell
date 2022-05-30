/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:25:24 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 15:25:29 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	freecmd(t_cmd cmd)
{
	if (cmd.pipe_in != STDIN_FILENO)
		close(cmd.pipe_in);
	if (cmd.pipe_out != STDOUT_FILENO)
		close(cmd.pipe_out);
	if (cmd.redir_in != STDIN_FILENO)
		close(cmd.redir_in);
	if (cmd.redir_out != STDOUT_FILENO)
		close(cmd.redir_out);
	free2d_array((void **)cmd.argv);
}

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
static char	*rl_get(void)
{
	static char const	*line_read;

	line_read = NULL;
	if (line_read == NULL)
	{
		free((char *)line_read);
		line_read = (char *) NULL;
	}
	line_read = readline(">>>");
	if (line_read == NULL)
		safe_exit(0);
	if (*line_read)
		add_history(line_read);
	return ((char *)line_read);
}

static int	iterate_cmds(t_pathlist *path, t_cmd *cmds, bool *exit)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmds[i].name)
	{
		*exit = !ft_strncmp("exit", cmds[i].name, 4);
		if (*exit)
			return (i);
		executor(path->path, &cmds[i++]);
	}
	i = 1;
	while (cmds[i].name)
	{
		waitpid(cmds[i].pid, &status, 0);
		if (!WIFEXITED(status))
			printf(" cmd %i returned: %i\n", i, WEXITSTATUS(status));
		freecmd(cmds[i++]);
	}
	insert(ft_strdup("?"), ft_itoa(WEXITSTATUS(status)));
	free(cmds);
	cmds = NULL;
	return (0);
}

void	loop_shell(t_pathlist *path)
{
	t_cmd	*cmds;
	t_token	*token_lst;
	bool	exit;
	int		i;

	i = 0;
	exit = false;
	define_exec_signals();
	while (!exit)
	{
		token_lst = lex(rl_get());
		cmds = parse(&token_lst);
		if (cmds && cmds[1].name)
			i = iterate_cmds(path, cmds, &exit);
	}
	while (cmds && cmds[i].argv)
		freecmd(cmds[i++]);
	free(cmds);
}
