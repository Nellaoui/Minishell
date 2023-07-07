# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

/*
ls

char **arr;

while (arr[i])
    access(arr[i], F_OK) == 0 cmd kanya else command not found


/usr/local/bin
/usr/bin/
/bin/ls
/usr/sbin
/sbin
/usr/local/munki
*/

int main(int ac, char **av, char **env)
{
    int fd[2]; // pipes
    pipe(fd);
    pid_t   pid;

    int fd2 = open("file", O_RDWR); // redirections
    dup2(fd2, STDOUT_FILENO);
    // pid = fork();
    // if (pid == 0)
    // {
    //     dup2(fd[1], STDOUT_FILENO);
    //     char *arr[] = {"/bin/ls", "-la", NULL};
    //     execve("/bin/ls", arr, env);
    // }
    // dup2(fd[0], STDIN_FILENO);
    char *arr[] = {"/bin/ls", "-la", NULL};
    execve("/bin/", arr, env);
    // char buf[1024];
    // read(fd[0], buf, 1000);
    // dprintf(2, "%s\n", buf);
    return (0);
}

// fd[0] == read_end pipe; 
// fd[1] == write_end pipe; 