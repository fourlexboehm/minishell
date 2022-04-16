/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashTable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:52:49 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 22:16:08 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Djb2 hash function
u_int64_t	hash(char *str)
{
	u_int64_t	hash;
	//char		c;

	hash = 5381L;
	while (*str++)
		hash = ((hash << 5) + hash) + (*str - 1);
	return (hash % 4096);
}

//returns an environmariable from a key
t_env	*search(char *key)
{
	unsigned long	hashindex;

	hashindex = hash(key);
	while (env_table[hashindex] != NULL)
	{
		if (!ft_strncmp(env_table[hashindex]->key, key, ft_strlen(key)))
			return (env_table[hashindex]);
		++hashindex;
		hashindex %= 4096;
	}
	return (NULL);
}

//insert a key-value pair into the hashtable
void	insert(char *key, char *data)
{
	t_env			*item;
	unsigned long	hashindex;

	item = (t_env *) malloc(sizeof(t_env));
	item->data = data;
	item->key = key;
	hashindex = hash(key);
	while (env_table[hashindex] != NULL
		&& (!ft_strncmp(env_table[hashindex]->key, "-1", 2)))
	{
		++hashindex;
		hashindex %= 4096;
	}
	env_table[hashindex] = item;
}

//return a list of env vars to the terminal
//todo make compat with pipes/redirects
void	display(void)
{
	int	i;

	i = 0;
	while (i < 4096)
	{
		if (env_table[i] != NULL)
			printf("%s=%s\n", env_table[i]->key, env_table[i]->data);
		i++;
	}
}

char	**get_env(void)
{
	int		i;
	char	*tmp;
	char	**env;
	//char	**envtemp;
	int		len;

	len = 0;
	i = 0;
	while (i < 4096)
		if (env_table[i++])
			len++;
	env = (char **)ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (++i < 4096)
	{
		if (env_table[i])
		{
			//envtemp = env;
			tmp = ft_strjoin(env_table[i]->key, "=");
			*env = ft_strjoin(tmp, env_table[i]->data);
			//ft_strlcat(*env, env_table[i]->data, 1);
			//free(envtemp);
			free(tmp);
			(*env)++;
		}
	}
	return (env);
}