#include <stdio.h>
#include <stdlib.h>
struct NODE
{
    char data;
    struct NODE *lchild, *rchild;
};
struct NODE *root;
struct NODE *root1;
struct queue
{
    char data;
    struct queue *next;
};
struct queue *head;
char lchild_data, rchild_data;

struct NODE *create_tree(char layer[], char in[], int l, int r, int k);
void pre_order(struct NODE *p);
void in_order(struct NODE *p);
void post_order(struct NODE *p);
void layer_order(struct NODE *p);
void visit(struct NODE *p);
void print_tree(struct NODE *p);
struct queue *init_queue(void);
int is_empty(struct queue *head);
void push_que(struct queue **head, char c);
char pop_que(struct queue **head);
void find_child(struct NODE *p, char c, int k);
void conc_print(struct NODE *p, int n);
int find_dep(struct NODE *p);
int verify(struct NODE *p);
struct NODE *copy(struct NODE *p);
void change_left_right(struct NODE *p);
void delete (struct NODE **p, char c);
void destroy(struct NODE *p);

int main()
{
    int i, k = 1;
    char layer[1000], in[1000];
    while (k != 0)
    {
        scanf("%d", &k);
        getchar();
        switch (k)
        {
        case 0:
            break;
        case 1:
            fgets(layer, 1000, stdin);
            fgets(in, 1000, stdin);
            for (i = 0; layer[i] != '\n'; i++)
                ;
            root = create_tree(layer, in, 0, i - 1, 0);
            break;
        case 2:
            print_tree(root);
            break;
        case 3:
            printf("depth:%d\n", find_dep(root) + 1);
            break;
        case 4:
            i = verify(root);
            if (i)
                printf("OK\n");
            else
                printf("ERROR\n");
            break;
        case 5:
            root1 = copy(root);
            print_tree(root1);
            break;
        case 6:
            change_left_right(root1);
            print_tree(root1);
            break;
        case 7:
            delete (&root, 'E');
            print_tree(root);
            break;
        case 8:
            destroy(root);
            destroy(root1);
            break;
        default:
            printf("bad command\n");
        }
    }
    return 0;
}

void pre_order(struct NODE *p)
{
    if (p == NULL)
        return;
    visit(p);
    pre_order(p->lchild);
    pre_order(p->rchild);
}
void in_order(struct NODE *p)
{
    if (p == NULL)
        return;
    in_order(p->lchild);
    visit(p);
    in_order(p->rchild);
}
void post_order(struct NODE *p)
{
    if (p == NULL)
        return;
    post_order(p->lchild);
    post_order(p->rchild);
    visit(p);
}
void visit(struct NODE *p)
{
    printf("%c", p->data);
}
void layer_order(struct NODE *p)
{
    char c;
    head = init_queue();
    while (!is_empty(head))
    {
        c = pop_que(&head);
        printf("%c", c);
        find_child(p, c, 0);
        if (lchild_data != '0')
            push_que(&head, lchild_data);
        find_child(p, c, 1);
        if (rchild_data != '0')
            push_que(&head, rchild_data);
    }
}
struct queue *init_queue(void)
{
    struct queue *p;
    p = (struct queue *)malloc(sizeof(struct queue));
    p->data = root->data;
    p->next = NULL;
    return p;
}
int is_empty(struct queue *head)
{
    return head == NULL;
}
void push_que(struct queue **head, char c)
{
    struct queue *p, *q = *head;
    p = (struct queue *)malloc(sizeof(struct queue));
    p->data = c;
    if (q == NULL)
    {
        *head = p;
        (*head)->next = NULL;
    }
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = p;
        p->next = NULL;
    }
}
char pop_que(struct queue **head)
{
    struct queue *p = *head;
    char c = p->data;
    *head = p->next;
    free(p);
    return c;
}
void find_child(struct NODE *p, char c, int k)
{
    if (p == NULL)
        return;
    else
    {
        if (p->data == c)
        {
            if (k == 0) //find lchild
            {
                if (p->lchild != NULL)
                    lchild_data = p->lchild->data;
                else
                    lchild_data = '0';
            }
            else
            {
                if (p->rchild != NULL)
                    rchild_data = p->rchild->data;
                else
                    rchild_data = '0';
            }
        }
        find_child(p->lchild, c, k);
        find_child(p->rchild, c, k);
    }
}
struct NODE *create_tree(char layer[], char in[], int l, int r, int k)
{
    if (l > r)
        return NULL;
    else
    {
        int i, j;
        struct NODE *p;
        p = (struct NODE *)malloc(sizeof(struct NODE));
        for (k = k; layer[k] != '\n'; k++)
            for (j = l; j <= r; j++)
                if (layer[k] == in[j])
                    goto end;
    end:
        p->data = layer[k];
        for (i = l; i <= r; i++)
            if (layer[k] == in[i])
                break;
        p->lchild = create_tree(layer, in, l, i - 1, k);
        p->rchild = create_tree(layer, in, i + 1, r, k);
        return p;
    }
}
void print_tree(struct NODE *p)
{
    struct NODE *root = p;
    printf("pre:");
    pre_order(root);
    printf("\n");
    printf("in:");
    in_order(root);
    printf("\n");
    printf("post:");
    post_order(root);
    printf("\n");
    printf("layer:");
    layer_order(root);
    printf("\n");
    conc_print(root, 0);
}
void conc_print(struct NODE *p, int n)
{
    if (p == NULL)
        return;
    int i;
    for (i = 0; i < n; i++)
        printf(" ");
    printf("%c\n", p->data);
    conc_print(p->lchild, n + 1);
    conc_print(p->rchild, n + 1);
}
int find_dep(struct NODE *p)
{
    int right_dep = 0, left_dep = 0;
    if (p == NULL)
        return -1;
    if (p->lchild != NULL)
        left_dep = find_dep(p->lchild);
    else
        left_dep = -1;
    if (p->rchild != NULL)
        right_dep = find_dep(p->rchild);
    else
        right_dep = -1;
    return (right_dep > left_dep) ? right_dep + 1 : left_dep + 1;
}
int verify(struct NODE *p)
{
    if (p == NULL)
        return 1;
    int flag = 1;
    flag=verify(p->lchild);
    if(flag==0)
    return 0;
    flag=verify(p->rchild);
    if (p->lchild != NULL && p->rchild != NULL)
    {
        if (p->data < p->lchild->data && p->data < p->rchild->data)
            return 1;
        else
            return 0;
    }
    else if (p->lchild != NULL && p->rchild == NULL)
    {
        if (p->data < p->lchild->data)
            return 1;
        else
            return 0;
    }
    else if (p->lchild == NULL && p->rchild != NULL)
    {
        if(p->data<p->rchild->data)
        return 1;
        else
        return 0;
    }
    else
    return 1;
    if(flag==0)
    return 0;
}
struct NODE *copy(struct NODE *p)
{
    if (p == NULL)
        return NULL;
    struct NODE *q;
    q = (struct NODE *)malloc(sizeof(struct NODE));
    q->data = p->data;
    q->lchild = copy(p->lchild);
    q->rchild = copy(p->rchild);
    return q;
}
void change_left_right(struct NODE *p)
{
    if (p->lchild == NULL && p->rchild == NULL)
        ;
    else
    {
        struct NODE *q = p->lchild;
        p->lchild = p->rchild;
        p->rchild = q;
    }

    if (p->lchild)
        change_left_right(p->lchild);
    if (p->rchild)
        change_left_right(p->rchild);
}
void delete (struct NODE **p, char c)
{
    if (*p == NULL)
        return;
    struct NODE *q = *p;
    if (q->data == c)
    {
        destroy(q);
        *p = NULL;
        return;
    }
    delete (&(q->lchild), c);
    delete (&(q->rchild), c);
}
void destroy(struct NODE *p)
{
    if (p == NULL)
        return;
    destroy(p->lchild);
    destroy(p->rchild);
    free(p);
}