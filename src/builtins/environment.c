
#include "../../inc/minishell.h"

void	pwd()
{
	printf("%s\n", getenv("PWD"));
}

void	export(t_pathlist	*path, int cmdnum)
{
	if (path->cmd[cmdnum]->args)
		insert(path->path[cmdnum], path->cmd[cmdnum]->args[0]);
}

void	unset(t_pathlist	*path, int cmdnum)
{
	env_table[hash(path->cmd[cmdnum]->args[0])] = NULL;
}