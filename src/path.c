
#include "../inc/minishell.h"

static bool	builtin(t_pathlist *path)
{
	if (!strcmp(path->cmd, "pwd"))
		pwd();
	else if (!strcmp(path->cmd, "env"))
		display();
	else if (!strcmp(path->cmd, "set"))
		set(path);
	else if (!strcmp(path->cmd, "unset"))
		unset(path);
//	else if (!strcmp(path->cmd, "cat"))
//		ls(path->args);
	else
		return (false);
	return (true);
}

//checks if a program exists and run it
void run_if_cmd(t_pathlist *path)
{
	int	i;
	char *file;

	if (builtin(path))
		return;
	i = 0;
	while(path->path)
	{
		file = ft_strjoin(path->path[i++], ft_strjoin("/", path->cmd));
		if (access( file, F_OK ) == 0 )
		{
			execv(file, path->args);
			return ;
		}
	}
	printf("%s Could not be run", path->cmd);
}

//takes the path from the the env_table and adds it to a 2d array in the pathlist
void	init_pathlist(t_pathlist *path)
{
	//path = malloc(sizeof (t_pathlist*));
	path->path = ft_split(search("PATH")->data, ':');
}