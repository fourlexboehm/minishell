#include <sys/stat.h>
#include "../inc/minishell.h"

static bool	builtin(t_cmd *cmd)
{
	if (!strcmp(cmd->name, "pwd"))
		pwd();
	else if (!strcmp(cmd->name, "cd"))
		cd(cmd->argv[1]);
	else if (!strcmp(cmd->name, "env"))
		display();
	else if (!strcmp(cmd->name, "export"))
		ft_export(cmd);
	else if (!strcmp(cmd->name, "unset"))
		unset(cmd);
	else
		return (false);
	return (true);
}

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
	int	*in_cpy;
	int	*out_cpy;

	in_cpy = cmd->redir_in;
	out_cpy = cmd->redir_out;
	if (cmd->pipe_in != STDIN_FILENO)
		dup2(cmd->pipe_in, STDIN_FILENO);
	if (cmd->pipe_out != STDOUT_FILENO)
		dup2(cmd->pipe_out, STDOUT_FILENO);
	while(in_cpy && *in_cpy != STDIN_FILENO)
			dup2(*in_cpy++, STDIN_FILENO);
	while(out_cpy && *out_cpy != STDIN_FILENO && *out_cpy != STDOUT_FILENO)
			dup2(*out_cpy++, STDOUT_FILENO);
}

//run a program if it's in PATH and executable
static void execute(t_cmd *cmd, char *file)
{
	char **env;

	cmd->pid = fork();
	//define_exec_signals();
	if (cmd->pid == -1)
	{
		printf("exec failed\n");
		exit(-1);
	}
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

//checks if a program exists as a builtin or in the path or in ./directory TODO run arbitrary directory files?
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
			if (!ft_strncmp(cmd->name, "./", 2))
				file = getfile(search("PWD").data, cmd->name + 2);
			else
				file = getfile(*cpy, cmd->name);
			if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
				return (execute(cmd, file));
			cpy++;
			free(file);
		}
	file = NULL;
	printf("%s Could not be run", cmd->name);
}