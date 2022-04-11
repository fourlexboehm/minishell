
#include "../../inc/minishell.h"

void	pwd()
{
	printf("%s\n", search("PWD")->data);
}

void	export(t_pathlist	*path)
{
	insert(path->args[0], path->args[1]);
}

void	unset(t_pathlist	*path)
{
	env_table[hash(path->args[0])] = NULL;
}