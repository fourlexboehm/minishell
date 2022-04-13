/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:34:15 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/04 11:42:01 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//copy the environment variables from **env into hashtable entries
void init_env_table(char **env)
{
	while (*env)
	{
		char **var;
//		int i;
//
//		i = 0;
//		while(i < 4096)
//			env_table[i++] = (t_env *)NULL;
//		i = 0;
//		while(i < 4096)
//			printf("%p", env_table[i++]);
		var = ft_split(*env++, '=');
		insert(var[0], var[1]);
		free(var);
	}
}

void	free_env()
{
	int i;

	i = 0;
	while (i < 4096)
	{
		if (env_table[i])
			free(env_table[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pathlist	lst;

	(void)argc;
	(void)argv;
	(void)env;

	init_env_table(env);
	//display();
	init_pathlist(&lst);
	if (lst.path)
		loop_shell(&lst);
	if (lst.cmd)

	destroy_pathlist(&lst);
	free_env();
	check_leaks();
}