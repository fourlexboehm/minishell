
#include "../inc/minishell.h"

//TODO implement
void	loop_shell(t_pathlist *path, t_cmd *cmd)
{
	//readline();
	path->cmd = "export";
	run_if_cmd(path);

	(void)cmd;
	(void)path;
}