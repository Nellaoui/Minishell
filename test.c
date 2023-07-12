# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_lt t_lt;

struct s_lt
{
    char    *data;
    t_lt    *next;
};

char    **lt_to_arr(t_lt *head)
{
    t_lt    *curr;
    char    **arr;

    curr = head;
    arr = (char **)malloc(sizeof(char *));
    int i = 0;
    while (curr)
    {
        arr[i] = strdup(curr->data);
        i++;
        curr = curr->next;
    }
    arr[i++] = 0;
    return (arr);
}

int main()
{
    t_lt    *head;

    head = malloc(sizeof(t_lt));
    head->data = strdup("/bin/ls");
    head->next  = malloc(sizeof(t_lt));
    head->next->data = strdup("-la");
    head->next->next = NULL;

    char **arr = lt_to_arr(head);
    for (int i = 0; arr[i]; i++)
        printf("%s\n", arr[i]);
    return (0);
}
