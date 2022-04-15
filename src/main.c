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

	while (*env)
	{
//		int i;
//
//		i = 0;
//		while(i < 4096)
//			env_table[i++] = (t_env *)NULL;
		var = ft_split(*env++, '=');
		insert(var[0], var[1]);
		free(var);
		//ft_freev((void **) var, 3, true);
	}
}

void	free_env(void)
{
	int	i;

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
	init_pathlist(&lst);
	if (lst.path)
		loop_shell(&lst);
	destroy_pathlist(&lst);
	free_env();
	check_leaks();
}
