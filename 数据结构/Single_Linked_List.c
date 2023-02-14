#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NODE
{
    int data;
    struct NODE *next;
};

struct NODE *create(void);
void insert(int n, struct NODE *head);
void dump(struct NODE *head);
void delete (int n, struct NODE *head);
void revert(struct NODE *head);
void sum(struct NODE *head);
void count(struct NODE *head);
void verify(struct NODE *head);
void destroy(struct NODE *head);

int main()
{
    struct NODE *head;
    char string[30];
    int num;
    while (scanf("%s", string))
    {
        if (strcmp(string, "create") == 0)
        {
            head = create();
            if (head == NULL)
            {
                printf("create failed\n");
                break;
            }
        }
        else if (strcmp(string, "insert") == 0)
        {
            scanf("%d", &num);
            insert(num, head);
        }
        else if (strcmp(string, "dump") == 0)
            dump(head);
        else if (strcmp(string, "delete") == 0)
        {
            scanf("%d", &num);
            delete (num, head);
        }
        else if (strcmp(string, "revert") == 0)
            revert(head);
        else if (strcmp(string, "sum") == 0)
            sum(head);
        else if (strcmp(string, "count") == 0)
            count(head);
        else if (strcmp(string, "verify") == 0)
            verify(head);
        else if (strcmp(string, "destroy") == 0)
            destroy(head);
        else if (strcmp(string, "bye") == 0)
            break;
        else
            printf("Bad command\n");
    }
    return 0;
}

struct NODE *create(void)
{
    struct NODE *head = NULL, *r;
    r = (struct NODE *)malloc(sizeof(struct NODE));
    if (r != NULL)
    {
        r->next = NULL;
        head = r;
        return r;
    }
    else
        return NULL;
}
void insert(int n, struct NODE *head)
{
    struct NODE *p, *q;
    if (head->next == NULL)
    {
        p = (struct NODE *)malloc(sizeof(struct NODE));
        if (p != NULL)
        {
            head->next = p;
            p->data = n;
            p->next = NULL;
        }
        else
            printf("insert failed\n");
    }
    else
    {
        p = head;
        while (p->next != NULL)
        {
            if (n > p->next->data)
                p = p->next;
            else
            {
                q = (struct NODE *)malloc(sizeof(struct NODE));
                if (q != NULL)
                {
                    q->data = n;
                    q->next = p->next;
                    p->next = q;
                }
                else
                    printf("insert failed\n");
                break;
            }
        }
        if (p->next == NULL)
        {
            q = (struct NODE *)malloc(sizeof(struct NODE));
            if (q != NULL)
            {
                q->data = n;
                p->next = q;
                q->next = NULL;
            }
            else
                printf("insert failed\n");
        }
    }
}
void dump(struct NODE *head)
{
    printf("{ ");
    struct NODE *p;
    for (p = head->next; p != NULL; p = p->next)
        printf("%d ", p->data);
    printf("}\n");
}
void delete (int n, struct NODE *head)
{
    struct NODE *p, *q;
    p = head;
    while (p->next != NULL)
    {
        if (p->next->data == n)
        {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else
            p = p->next;
    }
}
void revert(struct NODE *head)
{
    int n = 1, i, j;
    struct NODE *p = head->next, *q, *temp;
    if (p != NULL)
    {
        for (p = head->next; p->next != NULL; p = p->next)
            n++;
        p = head;
        for (i = 0; i < n - 1; i++)
        {
            temp = head;
            for (q = head->next; q->next != NULL; q = q->next)
                ;
            for (j = 0; j < n - 1; j++)
                temp = temp->next;
            q->next = p->next;
            p->next = q;
            p = q;
            temp->next = NULL;
        }
    }
}
void sum(struct NODE *head)
{
    struct NODE *p;
    long long int total = 0;
    for (p = head->next; p != NULL; p = p->next)
        total = total + p->data;
    printf("SUM: %lld\n", total);
}
void count(struct NODE *head)
{
    struct NODE *p;
    int n = 0;
    for (p = head->next; p != NULL; p = p->next)
        n++;
    printf("COUNT: %d\n", n);
}
void verify(struct NODE *head)
{
    struct NODE *p = head->next;
    if (p == NULL)
        printf("VERIFY: OK\n");
    else
    {
        while (p->next != NULL)
        {
            if (p->data <= p->next->data)
                p = p->next;
            else
            {
                printf("VERIFY: ERROR\n");
                break;
            }
        }
        if (p->next == NULL)
            printf("VERIFY: OK\n");
    }
}
void destroy(struct NODE *head)
{
    struct NODE *p = head, *q;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
}