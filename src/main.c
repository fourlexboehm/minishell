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
		var = ft_split(*env++, '=');
		insert(var[0], var[1]);
		free(var);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pathlist	lst;

	(void)argc;
	(void)argv;
	init_env_table(env);
	init_pathlist(&lst);
	loop_shell(&lst);
	destroy_pathlist(&lst);
	check_leaks();
}