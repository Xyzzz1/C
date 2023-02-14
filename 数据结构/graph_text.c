#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000
struct vertex
{
    char string[20];
    int num;
    struct edge *first_edge;
};
struct vertex *vex[MAX];
struct edge
{
    int adjvex;
    int weight;
    struct edge *next;
};
struct
{
    int adjvex;
    int low_cost;
} low_wieght[MAX];
struct
{
    int is_labeled;
    int is_passed;
    int distance;
    int pre;
} minimum_dist[MAX];
int visited[MAX];
int not_in[MAX];
int total;
struct vertex *init_graph(void);
void create_vertex(struct vertex *p);
void create_edge(struct vertex *p, int n);
void dump(void);
void DFS(struct vertex *p, int index);
void visit_vertex(struct vertex *p);
int spanning_tree(struct vertex *p, int index);
struct vertex *find_lowweight(int pre_total);
void update(struct vertex *p, int end_vertex);
int find_path(struct edge *q, int end_vertex, int k);
void Dijkstra(int start, int end);
void output_shortest_path(int start, int end);
int main()
{
    int N, i, index, total_weight, start, end, min;
    char string[20];
    while (scanf("%s", string))
    {
        if (strcmp(string, "CREATE") == 0)
        {
            scanf("%d", &N);
            vex[N] = NULL;
            total = N;
            for (i = 0; i < N; i++)
            {
                vex[i] = init_graph();
                visited[i] = 0;
                not_in[i] = 1;
            }
        }
        else if (strcmp(string, "VERTEX") == 0)
        {
            scanf("%d", &index);
            vex[index]->num = index;
            create_vertex(vex[index]);
        }
        else if (strcmp(string, "EDGE") == 0)
        {
            scanf("%d", &index);
            create_edge(vex[index], index);
        }
        else if (strcmp(string, "DUMP") == 0)
            dump();
        else if (strcmp(string, "DFS") == 0)
        {
            scanf("%d", &index);
            printf("DFS(%s):", vex[index]->string);
            DFS(vex[index], index);
            printf("\n");
        }
        else if (strcmp(string, "SPANNING-TREE") == 0)
        {
            scanf("%d", &index);
            total_weight = spanning_tree(vex[index], index);
            printf("\n        Weight of tree: %d\n", total_weight);
        }
        else if (strcmp(string, "SHORTEST-PATH") == 0)
        {
            for (i = 0; i < N; i++)
            {
                minimum_dist[i].distance = 1024 * 1024;
                minimum_dist[i].is_labeled = 0;
                minimum_dist[i].is_passed = 0;
                minimum_dist[i].pre = -1;
            }
            scanf("%d%d", &start, &end);
            Dijkstra(start, end);
            printf("SHORTEST-PATH(%s=>%s):", vex[start]->string, vex[end]->string);
            output_shortest_path(start, end);
            printf("\n        Distance %d\n", minimum_dist[end].distance);
        }
        else if (strcmp(string, "BYE") == 0)
            break;
    }
    return 0;
}
struct vertex *init_graph(void)
{
    struct vertex *p;
    p = malloc(sizeof(struct vertex));
    p->first_edge = NULL;
    return p;
}
void create_vertex(struct vertex *p)
{
    char string[20];
    int i, j = 0;
    fgets(string, 20, stdin);
    for (i = 0; string[i] != '\n'; i++)
    {
        if (string[i] == ' ')
            continue;
        p->string[j] = string[i];
        j++;
    }
    p->string[j] = '\0';
}
void create_edge(struct vertex *p, int n)
{
    int index, weight, i;
    scanf("%d", &index);
    scanf("%d", &weight);
    struct edge *temp, *q;
    for (i = 0; i < 2; i++)
    {
        if (i == 1)
        {
            p = vex[index];
            index = n;
        }
        temp = p->first_edge;
        q = malloc(sizeof(struct edge));
        p->first_edge = q;
        q->adjvex = index;
        q->weight = weight;
        q->next = temp;
    }
}
void dump(void)
{
    int i;
    struct edge *p;
    printf("GRATH DATA:\n");
    for (i = 0; i < total; i++)
    {
        printf("  %d:", i);
        printf("[%s]", vex[i]->string);
        for (p = vex[i]->first_edge; p != NULL; p = p->next)
            printf(" ->[%s]%d", vex[p->adjvex]->string, p->weight);
        printf("\n");
    }
}
void DFS(struct vertex *p, int index)
{
    struct edge *q = vex[index]->first_edge;
    if (!visited[index])
    {
        visit_vertex(p);
        visited[index] = 1;
        if (q)
            DFS(vex[q->adjvex], q->adjvex);
        else
            return;
    }
    else
        return;
    for (q = q; q && visited[q->adjvex]; q = q->next)
        ;
    if (!q)
        return;
    else
        DFS(vex[q->adjvex], q->adjvex);
}
void visit_vertex(struct vertex *p)
{
    printf(" %s", p->string);
}
int spanning_tree(struct vertex *p, int index)
{
    printf("SPANNING-TREE(%s):", p->string);
    int i, j, total_weight = 0;
    struct edge *q;
    low_wieght[0].adjvex = index;
    low_wieght[0].low_cost = 0;
    not_in[index] = 0;
    for (i = 1; i < total; i++)
    {
        p = find_lowweight(i);
        printf(" %s-", p->string);
        printf("%s(%d)", vex[low_wieght[i].adjvex]->string, low_wieght[i].low_cost);
    }
    for (i = 0; i < total; i++)
        total_weight = low_wieght[i].low_cost + total_weight;
    return total_weight;
}
struct vertex *find_lowweight(int pre_total)
{
    int i, min = 1024 * 1024;
    struct edge *q;
    struct vertex *p_head, *p_tail;
    for (i = 0; i < pre_total; i++)
        for (q = vex[low_wieght[i].adjvex]->first_edge; q != NULL; q = q->next)
            if (not_in[q->adjvex])
                if (q->weight < min)
                {
                    min = q->weight;
                    p_head = vex[low_wieght[i].adjvex];
                    p_tail = vex[q->adjvex];
                }
    not_in[p_tail->num] = 0;
    low_wieght[pre_total].low_cost = min;
    low_wieght[pre_total].adjvex = p_tail->num;
    return p_head;
}
void update(struct vertex *p, int end_vertex)
{
    if (p->num == end_vertex)
        return;
    int path_weight = 1024 * 1024, min = 1024 * 1024, i;
    struct edge *q;
    for (q = p->first_edge; q != NULL; q = q->next)
    {
        for (i = 0; i < total; i++)
            minimum_dist[i].is_passed = 0;
        if (minimum_dist[q->adjvex].is_labeled)
            path_weight = find_path(q, end_vertex, 1) + q->weight;
        if (path_weight)
            if (path_weight < min)
            {
                min = path_weight;
                minimum_dist[p->num].distance = min;
                minimum_dist[p->num].pre = q->adjvex;
            }
    }
}
int find_path(struct edge *q, int end_vertex, int k)
{
    if (minimum_dist[q->adjvex].is_passed || !minimum_dist[q->adjvex].is_labeled)
        return -q->weight;
    if (q->adjvex == end_vertex)
        return 0;
    int min = 1024 * 1024, temp, i;
    struct vertex *p = vex[q->adjvex];
    minimum_dist[q->adjvex].is_passed = k;
    for (q = p->first_edge; q != NULL; q = q->next)
    {
        for (i = 0; i < total; i++)
            if (minimum_dist[i].is_passed > k)
                minimum_dist[i].is_passed = 0;
        temp = find_path(q, end_vertex, k++) + q->weight;
        if (temp)
            if (temp < min)
                min = temp;
    }
    return min;
}
void Dijkstra(int start, int end)
{
    int times = 0, i, min;
    struct vertex *p = vex[start];
    minimum_dist[start].distance = 0;
    minimum_dist[start].is_labeled = 1;
    minimum_dist[start].pre = -1;
    times++;
    for (times = times; times < total; times++)
    {
        min = 1024 * 1024;
        for (i = 0; i < total; i++)
            update(vex[i], start);
        for (i = 0; i < total; i++)
            if (!minimum_dist[i].is_labeled)
                if (minimum_dist[i].distance < min)
                    min = minimum_dist[i].distance;
        for (i = 0; i < total; i++)
            if (!minimum_dist[i].is_labeled && minimum_dist[i].distance == min)
                minimum_dist[i].is_labeled = 1;
    }
}
void output_shortest_path(int start, int end)
{
    if (start == end)
    {
        printf(" %s",vex[end]->string);
        return;
    }
    output_shortest_path(start, minimum_dist[end].pre);
    printf(" %s", vex[end]->string);
}