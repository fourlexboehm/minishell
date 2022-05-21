#include "../../inc/minishell.h"

static void	define_value(char **value, char *key, t_env *local_vars)
{
	char *env_data;
	(void)local_vars;

	env_data = search(key).data;
	if (env_data)
		*value = ft_strdup(env_data);
	//TODO impl local vars
//	if (!*value)
//	{
//		env_data = local_search(key, local_vars).data;
//		if (env_data)
//			*value = ft_strdup(env_data);
//	}
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

void	expand(char **variable, bool dollar)
{
	t_env local_vars[local_env_size];
	char	*value;
	char	*key;
	char	*temp;
	bool	has_quote;

	value = NULL;
	has_quote = false;
	temp = *variable;
	has_quote = check_double_quotes(&temp, &key);
	if(dollar)
		temp++;
	define_value(&value, temp, local_vars);
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