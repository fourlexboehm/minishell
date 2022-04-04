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

int	main(int argc, char **argv, char **env)
{
	char **var;
	(void)argc;
	(void)argv;

	while (*env)
	{
		var = ft_split(*env, '=');
		insert(var[0], var[1]);
		env++;
	}
//
//	cmd = NULL;
//	l_command = NULL;
	display();
}
