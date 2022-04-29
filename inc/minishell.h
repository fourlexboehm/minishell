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
# include "typedefs.h"

//One allowed Global variable, it's the hash table that stores the environment variables
#define env_size 2048
#define local_env_size 256
extern t_env	g_env_table[env_size];

//environment functions
void		insert(char *key, char *data);
t_env		search(char *key);
char		**get_env(t_env *envtab);
void		display();
void		free_env();
u_int64_t	hash(char *str, int env_len);

//local environment functions
void	local_insert(char *key, char *data, t_env *env_local);
t_env	local_search(char *key, t_env *env_local);

//pathlist struct functions
void		init_pathlist(t_pathlist *path);
void		destroy_pathlist(t_pathlist *path);
void		executor(char **pathlist, t_cmd *cmds, int cmdnum);

//parser
t_cmd		*parse(t_token **lst);
t_token		*lex(char const *line, t_lex *lex_data);

//tokenUtils
int         is_whitespace(char c);
void        skip_whitespace(t_lex *lex_data);
t_token     *new_token(t_token **list);
void        handle_quote(t_token *token, t_lex *lex_data);

//tokenUtils2
void    smoke_pipes(t_token *token, t_lex *lex_data);
void    redir_l(t_token *token, t_lex *lex_data);
void    redir_r(t_token *token, t_lex *lex_data);
void    handle_rest(t_token *token, t_lex *lex_data);
void	free_tkn_lst(t_token **tkn_lst);


//repl
void		loop_shell(t_pathlist *path);

//builtins
void		cd(char *path);
void		pwd();
void		ft_export(t_cmd *cmds, int cmdnum);
void		unset(t_cmd *cmds, int cmdnum);

#endif