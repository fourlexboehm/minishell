
#include "../../inc/minishell.h"



//run a program if it's in PATH and executable
static void execute(t_cmd *cmd, char *file)
{
	char **env;

	cmd->pid = fork();
	//define_exec_signals();
	if (cmd->pid == -1)
		exit(printf("exec failed\n"));
	if (cmd->pid != 0)
	{
		free(file);
		file = NULL;
		return ;
	}
	env = get_env(g_env_table);
	setup_fds(cmd);
	execve(file, cmd->argv, env);
}

static bool add_if_var(char *name)
{
	char	*equals;
	//static	t_env[local_env_size];
	equals = ft_strchr(name, '=');
	if (!equals)
		return(false);
	insert(ft_substr(name, 0, equals - name), ft_strdup(equals + 1));
	//local_insert(ft_substr(name, 0, equals - name), ft_strdup(equals + 1));
	return(true);
}

//checks if a program exists as a builtin, in the path, as an absolute path or in ./directory
void	executor(char **path, t_cmd *cmd)
{
	struct stat	sb;
	char		*file;
	char 		**cpy;

	cpy = path;
	if (!cmd->name || cmd->name[0] == '\n'|| builtin(cmd))
		return ;
	while (*cpy)
		{
			if (*cmd->name == '/')
				file = ft_strdup(cmd->name);
			else if (!ft_strncmp(cmd->name, "./", 2))
				file = getfile(search("PWD").data, cmd->name + 2);
			else
				file = getfile(*cpy, cmd->name);
			if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
				return (execute(cmd, file));
			cpy++;
			free(file);
		}
	if (add_if_var(cmd->name))
		return ;
	printf("\n%s Could not be run\n", cmd->name);
}