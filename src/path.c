
#include <sys/stat.h>
#include "../inc/minishell.h"

char *getfile(const t_pathlist *path);

static bool	builtin(t_pathlist *path)
{
	if (!strcmp(path->cmd, "pwd"))
		pwd();
	else if (!strcmp(path->cmd, "env"))
		display();
	else if (!strcmp(path->cmd, "export"))
		export(path);
	else if (!strcmp(path->cmd, "unset"))
		unset(path);
	//TODO actually return to main and free stuff properly
	else if (!strcmp(path->cmd, "exit"))
		exit(-1);
	else
		return (false);
	return (true);
}

//string join a directory in path[] to the command name
char *getfile(const t_pathlist *path)
{
	char *file;
	char *subfile;
	int	i;

	i = 0;
	subfile = ft_strjoin("/", path->cmd);
	file = ft_strjoin(path->path[i++], subfile);
	free(subfile);
	return file;
}

//checks if a program exists and run it
void run_if_cmd(t_pathlist *path)
{
	struct stat sb;
	char *file;

	if (builtin(path))
		return;
	while(path->path)
	{
		file = getfile(path);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			execv(file, path->args);
			free(file);
			file = NULL;
			return ;
		}
		free(file);
	}
	file = NULL;
	printf("%s Could not be run", path->cmd);
}

//takes the path from the env_table and adds it to a 2d array in the pathlist
void	init_pathlist(t_pathlist *path)
{
	//path = malloc(sizeof (t_pathlist*));
	path->path = ft_split(search("PATH")->data, ':');
}

void	destroy_pathlist(t_pathlist *path)
{
	free(path->path);
	path->path = NULL;
}