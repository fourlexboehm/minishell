
#include "../../inc/minishell.h"

void	pwd()
{
	printf("%s\n", search("PWD")->data);
}

void	export(t_pathlist	*path, int cmdnum)
{
	char **vec;

	if (!path->cmd[cmdnum].args)
		return ;
	vec = ft_split(path->cmd[cmdnum].args[1], '=');
	insert(vec[0], vec[1]);
}

void	unset(t_pathlist	*path, int cmdnum)
{
	if (path->cmd[cmdnum].args)
		env_table[hash(path->cmd[cmdnum].args[1])] = NULL;
}