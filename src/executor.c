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

//run a program if it's in PATH and executable
static void execute(t_cmd *cmd, char *file)
{
	char **env;
	pid_t pid;
	int status;

	pid = fork();
	//define_exec_signals();
	if (pid == -1)
	{
		printf("exec failed\n");
		exit(-1);
	}
	if (pid == 0)
	{
		dup2();
		env = get_env(g_env_table);
		execve(file, cmd->argv, env);
		free2d_array((void **)env);
	}
	waitpid(pid, &status, 0);
	free(file);
	file = NULL;
	if (!WIFEXITED(status))
		printf("%i cmd returned:", status);
}

//checks if a program exists as a builtin or in the path
void	executor(char **path, t_cmd *cmd)
{
	struct stat	sb;
	char		*file;
	char 		**cpy;

	cpy = path;
	if (!cmd->name || cmd->name[0] == '\n'
		|| builtin(cmd))
		return ;
	//run local file if it starts with ./

	if (!ft_strncmp(cmd->name, "./", 2))
	{
		file = getfile(search("PWD").data, cmd->name + 2);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			execute(cmd, file);
			return ;
		}
	}
	else while (*cpy)
	{
		file = getfile(*cpy, cmd->name);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			execute(cmd, file);
			return ;
		}
		cpy++;
		free(file);
	}
	file = NULL;
	printf("%s Could not be run", cmd->name);
}
