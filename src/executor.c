#include <sys/stat.h>
#include "../inc/minishell.h"


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

static void setup_fds(t_cmd *cmd)
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


static void exec_builtin(void (function)(), t_cmd *cmd)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		setup_fds(cmd);
		(*function)(cmd);
	}
}

static bool	builtin(t_cmd *cmd)
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


//run a program if it's in PATH and executable
static void execute(t_cmd *cmd, char *file)
{
	char **env;

	cmd->pid = fork();
	//define_exec_signals();
	if (cmd->pid == -1)
		exit(printf("exec failed\n"));
	if (cmd->pid != 0)
	{
		free(file);
		file = NULL;
		return ;
	}
	env = get_env(g_env_table);
	setup_fds(cmd);
	execve(file, cmd->argv, env);
}

//checks if a program exists as a builtin, in the path, as an absolute path or in ./directory
void	executor(char **path, t_cmd *cmd)
{
	struct stat	sb;
	char		*file;
	char 		**cpy;

	cpy = path;
	if (!cmd->name || cmd->name[0] == '\n'
		|| builtin(cmd))
		return ;
	//run local file if it starts with ./ or search for it in the path
	while (*cpy)
		{
			if (*cmd->name == '/')
				file = ft_strdup(cmd->name);
			else if (!ft_strncmp(cmd->name, "./", 2))
				file = getfile(search("PWD").data, cmd->name + 2);
			else
				file = getfile(*cpy, cmd->name);
			if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
				return (execute(cmd, file));
			cpy++;
			free(file);
		}
	file = NULL;
	printf("\n%s Could not be run\n", cmd->name);
}