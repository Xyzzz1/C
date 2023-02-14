#include <stdio.h>
#define K 16

long long int r[1024 * 1024];
long long int min[17];
long long int length = 0;

void create_MinHeap(long long int num);
void swap(long long int *a, long long int *b);
long long int pop(void);
void adjust_heap(long long int index);
void record(void);

int main()
{
    long long int num, i;
    while (1)
    {
        scanf("%lld", &num);
        if (num == 0)
            break;
        else if (num == -1)
        {
            record();
            if (length < K)
                printf("Data (%lld):", length);
            else
                printf("Data (16):");
            for (i = 0; min[i] != -1; i++)
                printf(" %lld", min[i]);
            printf("\n");
        }
        else if (num == -2)
        {
            length=0;
        }
        else
        {
            r[length] = num;
            length++;
            create_MinHeap(num);
        }
    }
}
void create_MinHeap(long long int num)
{
    long long int index = length - 1, parent;
    parent = (long long int)(index - 1) / 2;
    for (index = length - 1; index && r[index] < r[parent]; parent = (long long int)(index - 1) / 2)
    {
        swap(&r[index], &r[parent]);
        index = parent;
    }
}
void swap(long long int *a, long long int *b)
{
    long long int temp = *b;
    *b = *a;
    *a = temp;
}
void adjust_heap(long long int index)
{
    long long int lchild, rchild, i, smaller;
    for (i = index; (lchild = 2 * i + 1) < length; i = smaller)
    {
        rchild = lchild + 1;
        if (rchild < length && r[rchild] < r[lchild])
            smaller = rchild;
        else
            smaller = lchild;
        if (r[i] < r[smaller])
            break;
        else
            swap(&r[i], &r[smaller]);
    }
}

long long int pop(void)
{
    long long int top = r[0];
    r[0] = r[length - 1];
    length--;
    return top;
}
void record(void)
{
    long long int i;
    for (i = 0; i < K && length; i++)
    {
        min[i] = pop();
        adjust_heap(0);
    }
    min[i] = -1;
    for (i = i - 1; i >= 0; i--)
    {
        r[length] = min[i];
        length++;
        create_MinHeap(min[i]);
    }
}