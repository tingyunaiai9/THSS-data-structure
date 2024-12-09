#include <stdio.h>

#define MAXN 1000000
#define MAXM 1000001
// #define MAXN 10
// #define MAXM 10

int max(int a, int b)
{
    return a > b ? a : b;
}

int n, m;

int queue[MAXN];
int queueHead = 0, queueTail = 0;

int head[MAXN]; // 邻接表头
int degree[MAXN]; // 节点的入度
int distance[MAXN]; // 节点到起点的距离

struct Edge
{
    int next; // 下一条边
    int to; // 目标节点
} edge[MAXM];

int edgeCount = 1;
void addEdge(int u, int v)
{
    edge[edgeCount].to = v;
    degree[v]++;
    edge[edgeCount].next = head[u]; // 将当前节点的第一条边设为原来的第一条边
    head[u] = edgeCount;
    edgeCount++;
}

int main()
{
    scanf("%d %d", &n, &m);

    int uu, vv;
    for (int i=0; i<m; i++)
    {
        scanf("%d %d", &uu, &vv);
        addEdge(uu, vv);
    }

    for (int i=1; i<=n; i++)
    {
        if (degree[i] == 0)
        {
            queue[queueTail++] = i;
            distance[i] = 1;
        }
    }

    while (queueHead <= queueTail)
    {
        int u = queue[queueHead++];
        for (int i = head[u]; i; i = edge[i].next) // 遍历 u 的所有边
        {
            int v = edge[i].to;
            distance[v] = max(distance[v], distance[u] + 1);
            degree[v]--;
            if (degree[v] == 0)
            {
                queue[queueTail++] = v;
            }
        }
    }

    int answer = 0;
    for (int i=1; i<=n; i++)
    {
        // printf("%d\n", distance[i]);
        answer = max(answer, distance[i]);
    }

    printf("%d\n", answer);

    return 0;
}
