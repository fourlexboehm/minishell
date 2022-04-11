
#include <sys/stat.h>
#include "../inc/minishell.h"

static bool	builtin(t_pathlist *path, int cmdnum)
{
	if (!strcmp(path->cmd[cmdnum]->name, "pwd"))
		pwd();
	else if (!strcmp(path->cmd[cmdnum]->name, "env"))
		display();
	else if (!strcmp(path->cmd[cmdnum]->name, "export"))
		export(path);
	else if (!strcmp(path->cmd[cmdnum]->name, "unset"))
		unset(path);
	else
		return (false);
	return (true);
}

//string join a directory in path[] to the command name
static char *getfile(const t_pathlist *path, int cmdnum)
{
	char *file;
	char *subfile;
	int	i;

	i = 0;
	subfile = ft_strjoin("/", path->cmd[cmdnum]->name);
	file = ft_strjoin(path->path[i++], subfile);
	free(subfile);
	return file;
}

//checks if a program exists and run it
void run_if_cmd(t_pathlist *path, int cmdnum)
{
	struct stat sb;
	char *file;
	pid_t	pid;

	if (builtin(path, cmdnum))
		return;
	while(path->path)
	{
		file = getfile(path, cmdnum);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			pid = fork();
			(void)pid;
			execv(file, path->cmd[cmdnum]->args);
			free(file);
			file = NULL;
			return ;
		}
		free(file);
	}
	file = NULL;
	printf("%s Could not be run", path->cmd[cmdnum]->name);
}

//takes the path from the env_table and adds it to a 2d array in the pathlist
void	init_pathlist(t_pathlist *path)
{
	path->path = ft_split(search("PATH")->data, ':');
}

void	destroy_pathlist(t_pathlist *path)
{
	free(path->path);
	path->path = NULL;
}