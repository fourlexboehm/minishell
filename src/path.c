
#include "../inc/minishell.h"

//void	check_if_builtin();
//{
//	if ()
//
//}

//checks if a program exists and adds its location to the path struct.
t_pathlist *check_if_cmd(t_pathlist *path, char *command)
{
	char *file;

	//check_if_builtin(path);
	while(path->path)
	{
		file = ft_strjoin(*path->path++, command);
		if (access( file, F_OK ) == 0 )
		{
			path->cmd1 = file;
			return (path);
		}
	}
	path->cmd1 = NULL;
	return (path);
}

//takes the path from the the env_table and adds it to a 2d array in the pathlist
t_pathlist *init_pathlist(t_pathlist *path)
{
	path = malloc(sizeof (t_pathlist*));
	path->path = ft_split(search("PATH")->data, ':');
	return (path);
}