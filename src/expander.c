#include "../inc/minishell.h"

static void	define_value(char **value, char *key)
{
	*value = ft_strdup(search(key, env_size)->data);
	//TODO impl local vars
//	if (!*value)
//		*value = ft_strdup(localsearch(localvars, key));
	if (!*value)
		*value = ft_strdup("");
}

static bool	check_double_quotes(char **temp, char **key)
{
	if (ft_strchr(*temp, '"'))
	{
		*key = ft_strtrim(*temp, "\"");
		return (true);
	}
	*key = ft_strdup(*temp);
	return (false);

}

static void	restore_quote(char **value, char **temp)
{
	*temp = ft_strjoin(*value, "\"");
	free(*value);
	*value = ft_strdup(*temp);
	free(*temp);
}

void	expand(char **variable)
{
	char	*value;
	char	*key;
	char	*temp;
	bool	has_quote;

	has_quote = false;
	temp = *variable;
	temp++;
	has_quote = check_double_quotes(&temp, &key);
	define_value(&value, key);
	free(*variable);
	free(key);
	if (has_quote)
		restore_quote(&value, &temp);
	*variable = value;
}