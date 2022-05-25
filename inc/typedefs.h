
#ifndef TYPEDEFS_H
# define TYPEDEFS_H

//Struct for each environment variable in hashTable
typedef struct s_env
{
	char	*key;
	char	*data;
}	t_env;

typedef struct s_lex
{
	char const		*line;
	int				i;
	struct s_token	*token_list;
	int				dlim_flag;
}	t_lex;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	int		argc;
	char	*name;
	int		pipe_in;
	int		pipe_out;
	int		redir_in;
	int		redir_out;
	int		pid;
	char	**argv;
}	t_cmd;

typedef struct s_var
{
	char	*before;
	char	*after;
	char	*value;
	char	*pointer;
}	t_var;

//Struct to store PATH
typedef struct s_pathlist
{
	char	**path;
}	t_pathlist;

#endif