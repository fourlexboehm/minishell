#include <sys/stat.h>
#include "../inc/minishell.h"

static bool	builtin(t_cmd *cmds, int cmdnum)
{
	if (!strcmp(cmds[cmdnum].name, "pwd"))
		pwd();
	else if (!strcmp(cmds[cmdnum].name, "cd"))
		cd(cmds[cmdnum].args[1]);
	else if (!strcmp(cmds[cmdnum].name, "env"))
		display();
	else if (!strcmp(cmds[cmdnum].name, "export"))
		ft_export(cmds, cmdnum);
	else if (!strcmp(cmds[cmdnum].name, "unset"))
		unset(cmds, cmdnum);
	else
		return (false);
	return (true);
}

//string join a directory in path[] to the command name
static char	*getfile(char **dir, t_cmd *cmds, int cmdnum)
{
	char	*file;
	char	*subfile;
	int		i;

	i = 0;
	subfile = ft_strjoin("/", cmds[cmdnum].name);
	file = ft_strjoin(dir[i++], subfile);
	free(subfile);
	subfile = NULL;
	return (file);
}

//run a program if it's in PATH and executable
static void execute(t_cmd *cmds, int cmdnum, char *file)
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
		env = get_env(g_env_table);
		execve(file, cmds[cmdnum].args, env);
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
void	executor(char **path, t_cmd *cmds, int cmdnum)
{
	struct stat	sb;
	char		*file;
	char 		**cpy;

	cpy = path;
	if (!cmds[cmdnum].name || cmds[cmdnum].name[0] == '\n')
		return ;
	if (builtin(cmds, cmdnum))
		return ;
	while (*cpy)
	{
		file = getfile(cpy, cmds, cmdnum);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			execute(cmds, cmdnum, file);
			return ;
		}
		cpy++;
		free(file);
	}
	file = NULL;
	printf("%s Could not be run", cmds[cmdnum].name);
}
