
#include "../../inc/minishell.h"

static void	change_dir_to_oldpwd(char *current_path)
{
	char * tmp;

	tmp = search("OLDPWD")->data;
	insert("OLDPWD", current_path);
	chdir(tmp);
}

static void cd_home()
{
	insert("OLDPWD", ft_strdup(search("PWD")->data));
	chdir(search("HOME")->data);
}

static void	change_dir_to_path(const char *current_path)
{
	char *wd;
	char *abspath;
	int	len;

	wd = search("PWD")->data;
	{
		len = ft_strlen(wd) + ft_strlen(current_path) + 1;
		insert("OLDPWD", ft_strdup(wd));
		if (current_path[0] == '/')
		{
			abspath = ft_calloc(len, sizeof(char));
			ft_strncat(abspath, wd, len);
			ft_strncat(abspath, "/", len);
			ft_strncat(abspath, current_path, len);
		}
		else
			abspath = ft_strdup(current_path);
		if (chdir(abspath))
			free(abspath);
		else
			insert("PWD", abspath);
	}
 }

void	cd(char *path)
{
	char	*current_path;

	if ((!path) || ft_strncmp(path, "~", 2) == 0 || ft_strncmp(path, "~/", 3) == 0)
		return cd_home();
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		current_path = ft_strdup(search("OLDPWD")->data);
		if (current_path == NULL)
		{
			//error_message("cd", NO_OLDPWD, 1);
			return ;
		}
		insert("OLDPWD", ft_strdup(search("PWD")->data));
		change_dir_to_oldpwd(current_path);
	}
	else
	{
		current_path = ft_strdup(path);
		change_dir_to_path(current_path);
	}
	free(current_path);
}