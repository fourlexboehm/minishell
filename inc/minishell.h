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

//Struct for each environment variable in hashTable
typedef struct s_env
{
	char *key;
	char *data;
} t_env;

//Struct to store PATH
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

//One allowed Global variable, it's the hash table that stores the environment variables
t_env	*env_table[4096];

//environment functions
void		insert(char *key, char *data);
t_env		*search(char *key);
void		display();
//pathlist struct functions
void		init_pathlist(t_pathlist *path);
void		destroy_pathlist(t_pathlist *path);

void		run_if_cmd(t_pathlist *path);

//
_Noreturn void		loop_shell(t_pathlist *path, t_cmd *cmd);
void		pwd();
uint64_t	hash(char *str);
void		export(t_pathlist	*path);
void		unset(t_pathlist	*path);




#endif
