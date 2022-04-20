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
u_int64_t	hash(char *str, int envlen)
{
	u_int64_t	hash;
	//char		c;

	hash = 5381L;
	while (*str++)
		hash = ((hash << 5) + hash) + (*str - 1);
	return (hash % envlen);
}

//returns an environmariable from a key
t_env	*search(char *key, int env_len)
{
	unsigned long	hashindex;

	hashindex = hash(key, env_len);
	while (env_table[hashindex]->key != NULL)
	{
		if (!ft_strncmp(env_table[hashindex]->key, key, ft_strlen(key)))
			return (env_table[hashindex]);
		++hashindex;
		hashindex %= env_size;
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
	hashindex = hash(key, env_size);
	while (env_table[hashindex] != NULL
		&& (!ft_strncmp(env_table[hashindex]->key, "-1", 2)))
	{
		++hashindex;
		hashindex %= env_size;
	}
	env_table[hashindex] = item;
}

//return a list of env vars to the terminal
//TODO make compat with pipes/redirects
void	display()
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		if (env_table[i] != NULL)
			printf("%s=%s\n", env_table[i]->key, env_table[i]->data);
		i++;
	}
}

char	**get_env(t_env **envtab)
{
	int		i;
	char	*tmp;
	char	**env;
	//char	**envtemp;
	int		len;

	len = 0;
	i = 0;
	while (i < env_size)
		if (envtab[i++])
			len++;
	env = (char **)ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (++i < env_size)
	{
		if (envtab[i])
		{
			tmp = ft_strjoin(envtab[i]->key, "=");
			*env = ft_strjoin(tmp, envtab[i]->data);
			free(tmp);
			(*env)++;
		}
	}
	return (env);
}