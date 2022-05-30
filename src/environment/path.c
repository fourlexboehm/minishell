/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:59:04 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 22:03:15 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//takes the path from the g_env_table and adds it to a 2d array in the pathlist
void	init_pathlist(t_pathlist *pathlist)
{
	t_env	path;

	path = search("PATH");
	if (path.key)
	{
		(get_path())->path = ft_split(path.data, ':');
		pathlist->path = get_path()->path;
	}
	else
		pathlist->path = NULL;
}

t_pathlist	*get_path(void)
{
	static t_pathlist	path;

	return (&path);
}

void	destroy_pathlist(void)
{
	free2d_array((void **)get_path()->path);
}
