#include "../../inc/minishell.h"

static void	define_value(char **value, char *key, t_env *local_vars)
{
	*value = ft_strdup(search(key).data);
	//TODO impl local vars
	if (!*value)
		*value = ft_strdup(local_search(key, local_vars).data);
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
	t_env local_vars[local_env_size];
	char	*value;
	char	*key;
	char	*temp;
	bool	has_quote;

	has_quote = false;
	temp = *variable;
	temp++;
	has_quote = check_double_quotes(&temp, &key);
	define_value(&value, key, local_vars);
	free(*variable);
	free(key);
	if (has_quote)
		restore_quote(&value, &temp);
	*variable = value;
}

void expandlst(t_token *lst)
{
	while (lst)
	{
		if (lst->type == t_single_quotes)
		{
			lst = lst->next;
			while(lst && lst->type != t_single_quotes)
				lst = lst->next;
		}
		else if (lst->type == t_command || lst->type == t_double_quotes)
		{
			expand_variables(&lst->value);
		}
		if (lst)
			lst = lst->next;
	}
}