/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashTable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:52:49 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/11 15:54:38 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Djb2 hash function
u_int64_t hash(char *str)
{
	u_int64_t hash;
	char c;

	hash = 5381L;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return(hash % 4096);
}

t_env *search(char *key)
{
	unsigned long	hashIndex;

	//get the hash 
	hashIndex = hash(key);
   //move in array until an empty 
	while(env_table[hashIndex] != NULL)
	{
		if(!ft_strncmp(env_table[hashIndex]->key, key,  ft_strlen(key)))
			return env_table[hashIndex];
		//go to next cell
		++hashIndex;
		//wrap around the table
		hashIndex %= 4096;
   }        
   return NULL;
}

void insert(char *key, char *data)
{
	t_env *item;
	unsigned long	hashIndex;

	item = (t_env *) malloc(sizeof(t_env));
	item->data = data;
	item->key = key;
	hashIndex = hash(key);
	while(env_table[hashIndex] != NULL && (!ft_strncmp(env_table[hashIndex]->key, "-1", 2)))
	{
		++hashIndex;
		hashIndex %= 4096;
	}
	env_table[hashIndex] = item;
}

void display()
{
	int i;

	i = 0;
	while (i < 4096)
	{
		if(env_table[i] != NULL)
			printf(" %s=%s\n",env_table[i]->key, env_table[i]->data);
		i++;
	}
}

char **get_env()
{
	int i;
	char *tmp;
	char **env;
	char **envtemp;

	env = malloc(sizeof(char *));
	*env = NULL;
	i = 0;
	while (i < 4096)
	{
		if(env_table[i] != NULL)
		{
			envtemp = env;
			env = malloc(sizeof (char *) + ft_strlen((char *) env));
			free(envtemp);
			tmp = ft_strjoin(env_table[i]->key, "=");
			*env = ft_strjoin(tmp, env_table[i]->data);
			free(tmp);
		}
		i++;
	}
	return (env);
}
