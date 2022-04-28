
#ifndef TYEPDEFS_H
# define TYEPDEFS_H

//Struct for each environment variable in hashTable
typedef struct s_env
{
	char *key;
	char *data;
	//struct s_env *next;
} t_env;

typedef	struct s_lex
{
	char	*line;
	int		i;
	struct s_token	*token_list;
}	t_lex;


typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

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

#endif