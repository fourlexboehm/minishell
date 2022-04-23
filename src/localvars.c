
#include "../inc/minishell.h"

t_env	*local_search(char *key, t_env **env_local)
{
	unsigned long	hashindex;

	hashindex = hash(key, local_env_size);
	while (env_local[hashindex]->key != NULL)
	{
		if (!ft_strncmp(env_local[hashindex]->key, key, ft_strlen(key)))
			return (env_local[hashindex]);
		++hashindex;
		hashindex %= local_env_size;
	}
	return (NULL);
}

void	local_insert(char *key, char *data, t_env **env_local)
{
	t_env			*item;
	unsigned long	hashindex;

	item = (t_env *) malloc(sizeof(t_env));
	item->data = data;
	item->key = key;
	hashindex = hash(key, local_env_size);
	while (env_local[hashindex] != NULL
		&& (!ft_strncmp(env_local[hashindex]->key, "-1", 2)))
	{
		++hashindex;
		hashindex %= local_env_size;
	}
	env_local[hashindex] = item;
}
