#include "../../inc/minishell.h"

int open_temp(void)
{
    int fd;

    fd = open("tmp/tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
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

void    read_n_write(char *delim, int has_quotes, int tmp_file)
{
    char    *line;

    signal(SIGINT, exit_heredoc);
    while (1)
    {
       line = readline("> ");
       if(!line)
       {
           close(tmp_file)
           exit(0);
       }

    }
}

void    heredoc(char *delimiter)
{
    int temp_fd;
    int pid;
    int has_quotes;
    int old_out;

    old_out = dup(1);
    has_quotes = 0;
    temp_fd = open_temp();
    if (delimiter[0] == "'" || delimiter[0] == '\"')
        has_quotes = 1;
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == 0)
        read_n_write(delimiter, has_quotes, temp_fd);
}