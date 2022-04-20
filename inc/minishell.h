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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

//Struct for each environment variable in hashTable
typedef struct s_env
{
	char *key;
	char *data;
	//struct s_env *next;
} t_env;

typedef struct s_cmd
{
	char *name;
	char **args;
} t_cmd;

//Struct to store PATH
typedef struct s_pathlist
{
	char **path;
	t_cmd *cmd;
} t_pathlist;

//One allowed Global variable, it's the hash table that stores the environment variables
#define env_size 2048
t_env	*env_table[env_size];

//environment functions
void		insert(char *key, char *data);
t_env		*search(char *key, int env_len);
char		**get_env(t_env **envtab);
void		display();
void		free_env();

//pathlist struct functions
void		init_pathlist(t_pathlist *path);
void		destroy_pathlist(t_pathlist *path);
void		run_if_valid_cmd(t_pathlist *path, int cmdnum);

//parser
t_cmd		*lex(char *line);
int 		n_str_in_vec(char **vec);

void		loop_shell(t_pathlist *path);
void		pwd();
u_int64_t	hash(char *str, int env_len);
void		export(t_pathlist	*path, int cmdnum);
void		unset(t_pathlist	*path, int cmdnum);





#endif
