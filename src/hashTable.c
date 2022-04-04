/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:52:49 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/04 12:20:05 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Djb2 hash function
uint64_t hash(char *str)
{
	unsigned long hash;
	int c;

	hash = 5381L;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash % 4096;
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

	item = (t_env*) malloc(sizeof(t_env));
	item->data = data;
	item->key = key;
   //get the hash
   hashIndex = hash(key);
   //move in array until an empty or deleted cell
   while(env_table[hashIndex] != NULL && (!ft_strncmp(env_table[hashIndex]->key, "-1", 2)))
   {
      //go to next cell
      ++hashIndex;
      //wrap around the table
      hashIndex %= 4096;
   }
   env_table[hashIndex] = item;
}

t_env* delete(t_env* item)
{
   char *key;
   unsigned long	hashIndex;
   t_env 			*temp;
   t_env 			*dummyItem;

   key = item->key;
   dummyItem = (t_env*) malloc(sizeof(t_env));
	dummyItem->data = "-1";
   dummyItem->key = "-1";
	hashIndex = hash(key);
   while(env_table[hashIndex] != NULL)
   {
      if(!ft_strncmp(env_table[hashIndex]->key, key, ft_strlen(key)))
	  {
         temp = env_table[hashIndex];
         env_table[hashIndex] = dummyItem;
         return temp;
      }
      ++hashIndex;
      hashIndex %= 4096;
   }      
   return NULL;
}

void display()
{
	int i = 0;

	while (i < 4096)
	{
		if(env_table[i] != NULL)
			printf(" %s=%s\n",env_table[i]->key, env_table[i]->data);
		i++;
	}
}