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

void	ft_export(t_pathlist	*path, int cmdnum)
{
	char	**vec;

	if (!path->cmd[cmdnum].args[1])
		return ;
	vec = ft_split(path->cmd[cmdnum].args[1], '=');
	insert(vec[0], vec[1]);
}

void	unset(t_pathlist	*path, int cmdnum)
{
	if (path->cmd[cmdnum].args[1])
		env_table[hash(path->cmd[cmdnum].args[1], env_size)].key = NULL;
}
