/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:59:04 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 22:03:15 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static char	*getfile(const t_pathlist *path, int cmdnum)
{
	char	*file;
	char	*subfile;
	int		i;

	i = 0;
	subfile = ft_strjoin("/", path->cmd[cmdnum].name);
	file = ft_strjoin(path->path[i++], subfile);
	free(subfile);
	return (file);
}

//checks if a program exists and run it
void	run_if_cmd(t_pathlist *path, int cmdnum)
{
	struct stat	sb;
	char		*file;
	pid_t		pid;
	char		**env;

	if (builtin(path, cmdnum))
		return ;
	while (path->path)
	{
		file = getfile(path, cmdnum);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			pid = fork();
			if (pid == -1)
			{
				printf("exec failed\n");
				exit(-1);
			}
			env = get_env();
			execve(file, path->cmd[cmdnum].args, env);
			free(file);
			ft_freev((void **) env, n_str_in_vec(env), true);
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
	t_env 	*path;

	path = search("PATH");
	if (path)
		pathlist->path = ft_split(path->data, ':');
	else
		pathlist->path = NULL;
}

void	destroy_pathlist(t_pathlist *path)
{
	if (path->path)
		ft_freev((void **) path->path, n_str_in_vec(path->path), true);
	//free(path->path);
	path->path = NULL;
}
