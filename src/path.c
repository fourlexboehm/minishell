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

#include <sys/stat.h>
#include "../inc/minishell.h"

//takes the path from the g_env_table and adds it to a 2d array in the pathlist
void	init_pathlist(t_pathlist *pathlist)
{
	t_env 	path;

	path = search("PATH");
	if (path.key)
		pathlist->path = ft_split(path.data, ':');
	else
		pathlist->path = NULL;
}

void	destroy_pathlist(t_pathlist *path)
{
	if (path->path)
		free2d_array((void **)path->path);
	path->path = NULL;
}
