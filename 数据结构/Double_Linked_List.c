#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NODE
{
    int data;
    struct NODE *next;
    struct NODE *prior;
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
        r->next = r;
        r->prior = r;
        head = r;
        return r;
    }
    else
        return NULL;
}
void insert(int n, struct NODE *head)
{
    struct NODE *p, *q;
    if (head->next == head)
    {
        p = (struct NODE *)malloc(sizeof(struct NODE));
        if (p != NULL)
        {
            p->data = n;
            p->next = head;
            p->prior = head;
            head->next = p;
            head->prior = p;
        }
        else
            printf("insert failed\n");
    }
    else
    {
        q = NULL;
        p = head->next;
        do
        {
            if (n > p->data)
                p = p->next;
            if (n <= p->data)
            {
                q = (struct NODE *)malloc(sizeof(struct NODE));
                if (q != NULL)
                {
                    q->data = n;
                    q->next = p;
                    q->prior = p->prior;
                    p->prior->next = q;
                    p->prior = q;
                }
                else
                    printf("insert failed\n");
                break;
            }
        } while (p->next != head);
        if (q == NULL)
        {
            if (p->next == head)
            {
                q = (struct NODE *)malloc(sizeof(struct NODE));
                if (q != NULL)
                {
                    q->data = n;
                    q->next = head;
                    q->prior = p;
                    head->prior = q;
                    p->next = q;
                }
                else
                    printf("insert failed\n");
            }
        }
    }
}
void dump(struct NODE *head)
{
    printf("{ ");
    struct NODE *p;
    for (p = head->next; p != head; p = p->next)
        printf("%d ", p->data);
    printf("}\n");
}
void delete (int n, struct NODE *head)
{
    struct NODE *p, *q;
    p = head;
    while (p->next != head)
    {
        p = p->next;
        if (p->data == n)
        {
            q = p;
            p = p->prior;
            q->prior->next = q->next;
            q->next->prior = q->prior;
            free(q);
        }
    }
}
void revert(struct NODE *head)
{
    int n = 0, i, temp;
    struct NODE *p, *q;
    if (p != NULL)
    {
        for (p = head; p->next != head; p = p->next)
            n++;
        p = head->next;
        q = head->prior;
        for (i = 0; i < (int)n/2; i++)
        {
            temp=p->data;
            p->data=q->data;
            q->data=temp;
            p=p->next;
            q=q->prior;
        }
    }
}
void sum(struct NODE *head)
{
    struct NODE *p;
    long long int total = 0;
    for (p = head->next; p != head; p = p->next)
        total = total + p->data;
    printf("SUM: %lld\n", total);
}
void count(struct NODE *head)
{
    struct NODE *p;
    int n = 0;
    for (p = head->next; p != head; p = p->next)
        n++;
    printf("COUNT: %d\n", n);
}
void verify(struct NODE *head)
{
    struct NODE *p = head->next;
    if (p == head)
        printf("VERIFY: OK\n");
    else
    {
        while (p->next != head)
        {
            if (p->data <= p->next->data)
                p = p->next;
            else
            {
                printf("VERIFY: ERROR\n");
                break;
            }
        }
        if (p->next == head)
            printf("VERIFY: OK\n");
    }
}
void destroy(struct NODE *head)
{
    struct NODE *p = head->next, *q;
    free(head);
    while (p != head)
    {
        q = p;
        p = p->next;
        free(q);
    }
}