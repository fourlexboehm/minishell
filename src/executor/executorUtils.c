#include "../../inc/minishell.h"

//string join a directory in path[] to the t_command name
char	*getfile(char *dir, char *name)
{
	char	*file;
	char	*subfile;

	subfile = ft_strjoin("/", name);
	file = ft_strjoin(dir, subfile);
	free(subfile);
	subfile = NULL;
	return (file);
}

void setup_fds(t_cmd *cmd)
{
	if (cmd->pipe_in != STDIN_FILENO)
	{
		dup2(cmd->pipe_in, STDIN_FILENO);
		//close(cmd->pipe_in);
		//cmd->pipe_in = STDIN_FILENO;
	}
	if (cmd->pipe_out != STDOUT_FILENO)
	{
		dup2(cmd->pipe_out, STDOUT_FILENO);
		//close(cmd->pipe_out);
		//cmd->pipe_out = STDOUT_FILENO;
	}
	if(cmd->redir_in  != STDIN_FILENO)
		dup2(cmd->redir_in, STDIN_FILENO);
	if(cmd->redir_out != STDOUT_FILENO)
		dup2(cmd->redir_out, STDOUT_FILENO);
}

void exec_builtin(void (function)(), t_cmd *cmd)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		setup_fds(cmd);
		(*function)(cmd);
	}
}

bool	builtin(t_cmd *cmd)
{
	if (!strcmp(cmd->name, "pwd"))
		exec_builtin(pwd, cmd);
	else if (!strcmp(cmd->name, "cd"))
		exec_builtin(cd, cmd);
	else if (!strcmp(cmd->name, "env"))
		exec_builtin(display, cmd);
	else if (!strcmp(cmd->name, "export"))
		exec_builtin(ft_export, cmd);
	else if (!strcmp(cmd->name, "unset"))
		exec_builtin(unset, cmd);
	else
		return (false);
	return (true);
}