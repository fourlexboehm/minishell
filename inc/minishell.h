/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:44:11 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/04 12:04:15 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char *key;
	char *data;
} t_env;

typedef struct s_pathlist
{
	char **path;
	char **args;
	char *cmd;
	//char *cmd2;
} t_pathlist;

typedef struct s_cmd
{
	char **commands;
} t_cmd;

t_env	*env_table[4096];

t_env		*delete(t_env* item);
void		insert(char *key, char *data);
t_env		*search(char *key);
void		display();
void		init_pathlist(t_pathlist *path);
void		run_if_cmd(t_pathlist *path);
void		loop_shell(t_pathlist *path, t_cmd *cmd);
void		pwd();
uint64_t	hash(char *str);
void		set(t_pathlist	*path);
void		unset(t_pathlist	*path);




#endif
