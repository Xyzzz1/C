#include <stdio.h>
#define N 5
struct
{
    int size;
    int val;
} items[N];
int knap(int space, int total_val, int i);
int main()
{
    int i, space, total_val = 0;
    printf("请分别输入%d个物品的体积和价值：", N);
    for (i = 0; i < N; i++)
        scanf("%d%d", &items[i].size, &items[i].val);
    printf("请输入背包容量：");
    scanf("%d", &space);
    total_val = knap(space, total_val, 0);
    printf("总价值：%d", total_val);
    return 0;
}
int knap(int space, int total_val, int i)
{
    int max = total_val;
    for (i = i; i < N; i++)
    {
        space = space - items[i].size;
        if (space >= 0)
        {
            max = knap(space, total_val + items[i].val, i);
            space=space+items[i].size;
        }
        else
        {
            space=space+items[i].size;
        }
    }
    if (total_val > max)
        max = total_val;
    return max;
}