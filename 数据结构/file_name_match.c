#include <stdio.h>
void match(char *w, char *n, int i, int j);
int main()
{
    char wildcard[100], name[100];
    int i = 0, j = 0;
    printf("请输入文件名通配符：");
    fgets(wildcard, 100, stdin);
    printf("请输入文件名：");
    fgets(name, 100, stdin);
    match(wildcard, name, i, j);
    return 0;
}
void match(char *w, char *n, int i, int j)
{
    if (w[i] == '*')
    {
        if (w[i + 1] == n[j] && w[i + 1] != n[j + 1])
            match(w, n, i + 1, j);
        else
            match(w, n, i, j + 1);
    }
    else if (w[i] == '?')
        match(w, n, i + 1, j + 1);
    else
    {
        if (n[j] == '\n')
            printf("SUCESS\n");
        else
        {
            if (w[i] != n[j])
                printf("FAIL\n");
            else
                match(w, n, i + 1, j + 1);
        }
    }
}