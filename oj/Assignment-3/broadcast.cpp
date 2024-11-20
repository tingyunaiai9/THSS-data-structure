#include <cstdio>

#define MAXN 10000
#define MAXM 60005

int n, m;
int result = 1; // 1: 可以  -1：不可以
int color[MAXN]; // 0: 未访问  1：黑  -1：白
int head[MAXN]; // 邻接表头

struct Edge
{
    int next; // 下一条边
    int to; // 目标节点
} edge[MAXM];

int edgeCount = 1;
void addEdge(int u, int v)
{
    edge[edgeCount].to = v;
    edge[edgeCount].next = head[u]; // 将当前节点的第一条边设为原来的第一条边
    head[u] = edgeCount;
    edgeCount++;
}

void dfs(int u, int c)
{
    if (result == -1)
        return;

    color[u] = c;
    for (int i = head[u]; i != 0; i = edge[i].next) // 遍历 u 的所有边
    {
        int v = edge[i].to;
        if (color[u] == color[v])
        {
            result = -1;
            return;
        }
        else if (color[v] == 0)
        {
            dfs(v, -c);
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);

    int u, v;
    for (int i=0; i<m; i++)
    {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    for (int i=0; i<n; i++)
    {
        if (color[i] == 0)
        {
            dfs(i, 1);
        }
    }

    printf("%d\n", result);
    return 0;
}
