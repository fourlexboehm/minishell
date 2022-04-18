#include <sys/stat.h>
#include "../inc/minishell.h"

static bool	builtin(t_pathlist *path, int cmdnum)
{
	if (!strcmp(path->cmd[cmdnum].name, "pwd"))
		pwd();
	else if (!strcmp(path->cmd[cmdnum].name, "env"))
		display();
	else if (!strcmp(path->cmd[cmdnum].name, "export"))
		export(path, cmdnum);
	else if (!strcmp(path->cmd[cmdnum].name, "unset"))
		unset(path, cmdnum);
	else
		return (false);
	return (true);
}

//string join a directory in path[] to the command name
static char	*getfile(char **dir, t_pathlist *path, int cmdnum)
{
	char	*file;
	char	*subfile;
	int		i;

	i = 0;
	subfile = ft_strjoin("/", path->cmd[cmdnum].name);
	file = ft_strjoin(dir[i++], subfile);
	free(subfile);
	subfile = NULL;
	return (file);
}

//run a program if it's in PATH and executable
static void execute(t_pathlist *path, int cmdnum, char *file)
{
	char **env;
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		printf("exec failed\n");
		exit(-1);
	}
	if (pid == 0)
	{
		env = get_env();
		execve(file, path->cmd[cmdnum].args, env);
		free2d_array((void **)env);
		//ft_freev((void **) env, n_str_in_vec(env), true);
	}
	waitpid(pid, &status, 0);
	free(file);
	file = NULL;
	if (!WIFEXITED(status))
		printf("%i cmd returned:", status);
}

//checks if a program exists as a builtin or in the path
void	run_if_valid_cmd(t_pathlist *path, int cmdnum)
{
	struct stat	sb;
	char		*file;
	char 		**cpy;

	cpy = path->path;
	if (!path->cmd[cmdnum].name || path->cmd[cmdnum].name[0] == '\n')
		return ;
	if (builtin(path, cmdnum))
		return ;
	while (*cpy)
	{
		file = getfile(cpy, path, cmdnum);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			execute(path, cmdnum, file);
			return ;
		}
		cpy++;
		free(file);
	}
	file = NULL;
	printf("%s Could not be run", path->cmd[cmdnum].name);
}
