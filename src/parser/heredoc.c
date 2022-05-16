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

void    read_n_write(char *delim, int has_quotes, int tmp_file)
{
    char    *line;
    char    *temp[100];
    int j;
    int i;

    i = 0;
    signal(SIGINT, exit_heredoc);
    while (1)
    {
       line = readline("> ");
       if(!line)
       {
           close(tmp_file);
           exit(0);
       }
	   if (line[0] == '\n')
		   continue ;
        if (!ft_strncmp(line, delim, ft_strlen(delim)))
            return ;
        while (line[i]) 
        {
            if (line[i] == '$' && has_quotes == 0)
            {
                if(line[++i] > 'A' && line[i] < 'Z')
                {
                    j = 0;
                    while (line[i] != ' ')
                    {
                        *temp[j] = line[i];
                        i++;
                        j++;
                    }
                    *temp[++j] = '\0';
                    expand(temp);
                    ft_putstr_fd(*temp, tmp_file);
                }

            }
            else 
                ft_putchar_fd(line[i], tmp_file);
        }
    }
}

void    heredoc(char *delimiter)
{
    int temp_fd;
    //int pid;
    int has_quotes;
//    int old_out;
//
//    old_out = dup(1);
    has_quotes = 0;
    temp_fd = open_temp();
    if (delimiter[0] == '\'' || delimiter[0] == '"')
        has_quotes = 1;
   //signal(SIGINT, SIG_IGN);
    //pid = fork();
    //if (pid == 0)
        read_n_write(delimiter, has_quotes, temp_fd);
}