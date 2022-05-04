/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:56:23 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 21:57:06 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pwd(void)
{
	printf("%s\n", search("PWD").data);
}

void	ft_export(t_cmd *cmds, int cmdnum)
{
	char	**vec;

	if (!cmds[cmdnum].argv[1])
		return ;
	vec = ft_split(cmds[cmdnum].argv[1], '=');
	insert(vec[0], vec[1]);
}

void	unset(t_cmd *cmds, int cmdnum)
{
	if (cmds[cmdnum].argv[1])
		g_env_table[hash(cmds[cmdnum].argv[1], env_size)].key = NULL;
}
