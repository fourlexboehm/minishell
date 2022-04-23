/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:34:15 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 22:23:39 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//copy the environment variables from **env into hashtable entries
void	init_env_table(char **env)
{
	char	**var;
	int i;

	i = 2;
	while(i < env_size)
	{
		env_table[i].key = NULL;
		env_table[i].data = NULL;
		i++;
	}
	while (*env)
	{
		var = ft_split(*env++, '=');
		if (var[1])
		{
			insert(var[0], var[1]);
		}
		if (var[i])
			while(var[i])
				free(var[i++]);
		free(var);
	}
}

void	free_env(void)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		if (env_table[i].key)
		{
			free(env_table[i].data);
			free(env_table[i].key);
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pathlist	lst;

	(void)argc;
	(void)argv;
	init_env_table(env);
	init_pathlist(&lst);
	if (lst.path)
		loop_shell(&lst);
	destroy_pathlist(&lst);
	free_env();
	check_leaks();
}
