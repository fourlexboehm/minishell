/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:25:55 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:33:44 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//run a program if it's in PATH and executable
static void	execute(t_cmd *cmd, char *file)
{
	char	**env;

	cmd->pid = fork();
	define_exec_signals();
	if (cmd->pid == -1)
		safe_exit(printf("exec failed\n"));
	if (cmd->pid != 0)
	{
		if ((cmd + 1)->name)
			close(cmd->pipe_out);
		if ((cmd - 1)->name)
			close(cmd->pipe_in);
		free(file);
		file = NULL;
		return ;
	}
	env = get_env(g_env_table);
	setup_fds(cmd);
	execve(file, cmd->argv, env);
}

//local_insert(ft_substr(name, 0, equals - name), ft_strdup(equals + 1));
//static	t_env[LOCAL_ENV_SIZE];
static bool	add_if_var(char *name)
{
	char	*equals;

	equals = ft_strchr(name, '=');
	if (!equals)
		return (false);
	insert(ft_substr(name, 0, equals - name), ft_strdup(equals + 1));
	return (true);
}

/*checks if a program exists as a builtin, 
 * in the path, as an absolute path or in ./directory
 */
void	executor(t_cmd *cmd)
{
	struct stat	sb;
	char		*file;
	char		**path;

	path = init_pathlist();
	if (!path || !cmd->name || builtin(cmd))
		return ;
	while (*path)
	{
		if (*cmd->name == '/')
			file = ft_strdup(cmd->name);
		else if (!ft_strncmp(cmd->name, "./", 2))
			file = getfile(search("PWD").data, cmd->name + 2);
		else
			file = getfile(*path, cmd->name);
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
			return (execute(cmd, file));
		path++;
		free(file);
	}
	if (add_if_var(cmd->name))
		return ;
	printf("\n%s Could not be run\n", cmd->name);
	destroy_pathlist(path);
}
