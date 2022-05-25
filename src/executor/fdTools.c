/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdTools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:21:38 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:21:39 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	secure_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	close_std_streams(void)
{
	secure_close(0);
	secure_close(1);
}

void	close_saved_fd_and_streams(t_cmd *procs)
{
	if (procs)
	{
		secure_close(procs->saved_std[0]);
		secure_close(procs->saved_std[1]);
		close_std_streams();
	}
}

void	close_all_streams_except_current(t_cmd *cmd, int i)
{
	int	k;

	k = 0;
	while ((cmd + k))
	{
		if (k != i)
		{
			secure_close(cmd[k].pipe_out);
			secure_close(cmd[k].pipe_in);
		}
		k++;
	}
}
