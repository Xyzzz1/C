#include <stdio.h>
#include <stdlib.h>
struct NODE
{
    char data;
    struct NODE *next;
};
struct NODE *top = NULL;
int is_empty(struct NODE **top);
void push(struct NODE **ptop, char data);
void pop(struct NODE **ptop);
char get_top(struct NODE **ptop);

int main()
{
    int i;
    char string[200];
    fgets(string, 200, stdin);
    for (i = 0; string[i] != '\n'; i++)
    {
        if (string[i] == '(' || string[i] == '[')
            push(&top, string[i]);
        else if (string[i] == ')')
        {
            if (is_empty(&top))
                break;
            else if (get_top(&top) == '(')
                pop(&top);
            else
                break;
        }
        else if (string[i] == ']')
        {
            if (is_empty(&top))
                break;
            else if (get_top(&top) == '[')
                pop(&top);
            else
                break;
        }
    }
    if (string[i] == '\n' && top == NULL)
        printf("配对\n");
    else
        printf("不配对\n");
    return 0;
}

int is_empty(struct NODE **top)
{
    return top == NULL;
}
void push(struct NODE **ptop, char x)
{
    struct NODE *p = (struct NODE *)malloc(sizeof(struct NODE));
    p->data = x;
    p->next = *ptop;
    *ptop = p;
}
void pop(struct NODE **ptop)
{
    struct NODE *p = *ptop;
    char s;
    s = p->data;
    *ptop = p->next;
    free(p);
}
char get_top(struct NODE **ptop)
{
    struct NODE *p = *ptop;
    return p->data;
}