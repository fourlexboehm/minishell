
#include "../../inc/minishell.h"

static bool	is_exit_status_variable(char **value)
{
	if (ft_strncmp(*value, "$?", 3) == 0)
	{
		free(*value);
		return (true);
	}
	return (false);
}

static void	deal_with_string_slices(t_var *var, char **value, int *i)
{
	var->before = ft_substr(*value, 0, *i);
	var->value = ft_substr(*value, *i, get_var_size(var->pointer, i));
	if (ft_strchr(var->value, '\''))
		handle_var_single_quote(var, value, *i);
	else
		var->after = ft_substr(*value, *i, (ft_strlen(*value) - *i));
	expand(&var->value, true);
}

static bool	has_dollar_sign(char **value, t_var *var, int *i)
{
	if (!(*value) || is_exit_status_variable(value))
		return (false);
	var->pointer = search_var(*value, i);
	if (!(var->pointer))
		return (false);
	return (true);
}

static bool	only_dollar_sign_between_quotes(char **value)
{
	if (!ft_strncmp(*value, "\"$\"", 4))
	{
		free(*value);
		*value = ft_strdup("$");
		return (true);
	}
	return (false);
}

void	expand_variables(char **value)
{
	t_var	var;
	char	*new_str;
	char	*tmp_str;

	int		i;
	i = 0;
	if (!has_dollar_sign(value, &var, &i)
		|| only_dollar_sign_between_quotes(value))
		return ;
	deal_with_string_slices(&var, value, &i);
	tmp_str = ft_strjoin(var.before, var.value);
	new_str = ft_strjoin(tmp_str, var.after);
	free(tmp_str);
	free(var.before);
	free(var.after);
	free(*value);
	*value = new_str;
	expand_variables(value);
}

