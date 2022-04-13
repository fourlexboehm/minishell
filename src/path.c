
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
static char *getfile(const t_pathlist *path, int cmdnum)
{
	char *file;
	char *subfile;
	int	i;

	i = 0;
	subfile = ft_strjoin("/", path->cmd[cmdnum].name);
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
			if(pid==-1)
			{
				printf("exec failed\n");
				exit(-1);
			}
			execve(file, path->cmd[cmdnum].args, get_env());
			if (pid == 0)
			{
				(execve(file, path->cmd[cmdnum].args, get_env()));
			}
			free(file);
			file = NULL;
			return ;
		}
		path->path++;
		free(file);
	}
	file = NULL;
	printf("%s Could not be run", path->cmd[cmdnum].name);
}

//takes the path from the env_table and adds it to a 2d array in the pathlist
void	init_pathlist(t_pathlist *pathlist)
{
	//t_env *pathvar;
	char* path = search("PATH")->data;

	//pathvar = search("PATH");
	if (path)
		pathlist->path = ft_split(path, ':');
	else
		pathlist->path = NULL;
}

void	destroy_pathlist(t_pathlist *path)
{
	free(path->path);
	path->path = NULL;
}