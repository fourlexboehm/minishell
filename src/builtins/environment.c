
#include "../../inc/minishell.h"

void	pwd()
{
	printf("%s\n", search("PWD")->data);
}

void	export(t_pathlist	*path, int cmdnum)
{
	insert(path->path[cmdnum], path->cmd[cmdnum]->args[0]);
}

void	unset(t_pathlist	*path, int cmdnum)
{
	env_table[hash(path->cmd[cmdnum]->name)] = NULL;
}