#include "../../inc/minishell.h"

int open_temp(void)
{
    int fd;

    unlink("/tmp/tmp_file");
    fd = open("/tmp/tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
        printf("ERROR TEMP FD FAILED\n");
    return(fd);
}

void    exit_heredoc(int signal)
{
    (void)signal;
    write(1, "/n", 1);
    exit (0);
}

static int get_var_len(char *line, const int *i)
{
    int var_len;
    int c;
    c = *i;
    c++;
    var_len = 0;
    if(ft_isalpha(line[c]))
    {
        while (ft_isalpha(line[c]) && line[c] != ' ' && line[c] != '\0')
        {
            var_len++;
            c++;
        }
        return (var_len);
    }
    return(0);
}

static int   heredoc_var(char *line, int *i, int tmp_file)
{
    char    *temp;
    int j;
    int c;
    int len;
    j = 0;
    c = *i;
    c++;
    len = get_var_len(line, i);
    temp = (char *)malloc(sizeof(len + 1));
    if(ft_isalpha(line[c]))
    {
        while (line[c] != ' ' && line[c])
        {
            temp[j] = line[c];
            c++;
            j++;
        }
        temp[j] = '\0';
        //printf("temp is %s", temp);
        expand(&temp);
        ft_putstr_fd(temp, tmp_file);

    }
    return (len);
}

void    read_n_write(char *delim, int has_quotes, int tmp_file)
{
    char    *line;
    int i;
    int skip_var_name;

    signal(SIGINT, exit_heredoc);
    while (1)
    {
        i = 0;
       line = readline("> ");
       if(!line)
       {
           close(tmp_file);
           exit(0);
       }
	   if (line[0] == '\n')
		   continue ;
        if (!ft_strncmp(line, delim, ft_strlen(delim)))
        {
            close(tmp_file);
            exit(0);
        }
        while (line[i]) 
        {
            //printf("line[i] is %c and hasQ is %i\n", line[i], has_quotes);
            if (line[i] == '$' && has_quotes == 0)
            {
               skip_var_name = heredoc_var(line, &i, tmp_file);
                i += skip_var_name; 
            }
            else 
                ft_putchar_fd(line[i], tmp_file);
            i++;
        }
        ft_putchar_fd('\n', tmp_file);
    }
}

void    heredoc(char *delimiter)
{
    int temp_fd;
    int pid;
    int has_quotes;
    int status;

    has_quotes = 0;
    temp_fd = open_temp();
    if (delimiter[0] == '\'' || delimiter[0] == '"')
    {
        has_quotes = 1;
        delimiter = ft_strtrim(delimiter, "\"'");
    }
    //signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == 0)
        read_n_write(delimiter, has_quotes, temp_fd);
    close(temp_fd);
	waitpid(pid, &status, 0);
	if (!WIFEXITED(status))
        printf("error PID status\n");
}