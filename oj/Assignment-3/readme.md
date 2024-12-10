# Assignment-3 Report

## 1 broadcast

### 1.1 题目分析

本题使用 dfs 遍历，相邻结点标记为不同的颜色，若能遍历完整张图且无颜色冲突，则有解

时间复杂度 $O(n+m)$

### 1.2 代码实现

```cpp
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
```

## 2 postman

### 2.1 题目分析

本题的图为有向无环图，可使用拓扑排序遍历

同时使用动态规划更新到达该结点的最长距离，状态转移方程为：

>distance[v] = max(distance[v], distance[u] + 1)

时间复杂度 $O(m+n)$

### 2.2 代码实现

```cpp
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
```

## 3 temperature

### 3.1 题目分析

本题使用 2-D Tree

在 2-D Tree 的每个节点保存

1. 该节点的相关信息
2. 以它为根子树的总节点数量
3. 以它为根子树的总气温

建树过程中

* 使用快速选择算法求中位数，时间复杂度 $O(n)$
* 递归建树，时间复杂度 $O(n \lg n)$

单次查询复杂度 $O(\sqrt n)$，总查询复杂度 $O(m \sqrt n)$

总时间复杂度 $O(n \lg n + m \sqrt n)$

### 3.2 代码实现

```cpp
// #pragma GCC optimize(2)

#include "temperature.h"
// #include "temperature_lib.c"

#include <cstdio>

#define MaxN 50005

template <typename T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

struct pair
{
    long long first; // 总温度
    int second; // 观测站数量
};

pair make_pair(long long first, int econd)
{
    return (pair){first, econd};
}

struct node
{
    int x, y;
    long long value;
};

int query_x_left, query_x_right, query_y_left, query_y_right; // 查询范围

// 第 n 的元素是第 n 小的元素
// 前小后大
template <typename Compare>
void nth_element(int *first, int *nth, int *last, Compare comp);

struct KDTree
{
    node tree_node[MaxN]; // 结点
    long long sum[MaxN]; // 总温度

    int lc[MaxN], rc[MaxN]; // 左右子树
    int size[MaxN];
    int node_indices[MaxN]; //节点的索引

    // 边界
    int Left[MaxN], Right[MaxN];
    int Up[MaxN], Down[MaxN];

    void pushup(int x) // 更新结点信息
    {
        size[x] = size[lc[x]] + size[rc[x]] + 1;
        sum[x] = sum[lc[x]] + sum[rc[x]] + tree_node[x].value;

        // 更新边界
        Left[x] = tree_node[x].x;
        Right[x] = tree_node[x].x;
        Up[x] = tree_node[x].y;
        Down[x] = tree_node[x].y;

        if (lc[x])
        {
            Left[x] = min(Left[x], Left[lc[x]]);
            Right[x] = max(Right[x], Right[lc[x]]);
            Up[x] = min(Up[x], Up[lc[x]]);
            Down[x] = max(Down[x], Down[lc[x]]);
        }
        if (rc[x])
        {
            Left[x] = min(Left[x], Left[rc[x]]);
            Right[x] = max(Right[x], Right[rc[x]]);
            Up[x] = min(Up[x], Up[rc[x]]);
            Down[x] = max(Down[x], Down[rc[x]]);
        }
    }

    int build(int left, int right, int c)
    {
        if (left > right)
        {
            return 0;
        }

        int mid = (left + right) / 2;
        if (c) // 按 x 坐标排序
        {
            nth_element(node_indices + left, node_indices + mid, node_indices + right + 1, [&](int a, int b)
                            { return tree_node[a].x < tree_node[b].x; });
        }
        else // 按 y 坐标排序
        {
            nth_element(node_indices + left, node_indices + mid, node_indices + right + 1, [&](int a, int b)
                            { return tree_node[a].y < tree_node[b].y; });
        }

        if (mid > left)
        {
            lc[node_indices[mid]] = build(left, mid - 1, c ^ 1);
        }
        if (mid < right)
        {
            rc[node_indices[mid]] = build(mid + 1, right, c ^ 1);
        }

        pushup(node_indices[mid]);

        return node_indices[mid];
    }

    pair query(int x)
    {
        if (!x) // 空结点
        {
            return make_pair(0, 0);
        }

        // 不交
        if (query_x_left > Right[x] || Left[x] > query_x_right || query_y_left > Down[x] || Up[x] > query_y_right)
        {
            return make_pair(0, 0);
        }

        // 内含
        if (query_x_left <= Left[x] && Right[x] <= query_x_right && query_y_left <= Up[x] && Down[x] <= query_y_right)
        {
            return make_pair(sum[x], size[x]);
        }

        int X = tree_node[x].x, Y = tree_node[x].y;

        pair result = make_pair(0, 0);
        pair left_result, right_result;

        if (query_x_left <= X && X <= query_x_right && query_y_left <= Y && Y <= query_y_right)
        {
            result.first += tree_node[x].value;
            result.second++;
        }

        left_result = query(lc[x]);
        right_result = query(rc[x]);

        result.first = result.first + left_result.first + right_result.first;
        result.second = result.second + left_result.second + right_result.second;

        return result;
    }
};

KDTree T;

int main()
{
    int n = GetNumOfStation();

    for (int i = 1; i <= n; i++)
    {
        int x, y, temp;
        GetStationInfo(i - 1, &x, &y, &temp);
        T.tree_node[i].x = x;
        T.tree_node[i].y = y;
        T.tree_node[i].value = temp;
        T.node_indices[i] = i;
    }

    int root = T.build(1, n, 1); // 构建 KD 树

    while (GetQuery(&query_x_left, &query_y_left, &query_x_right, &query_y_right))
    {
        pair result = T.query(root);
        long long sum = result.first;
        int size = result.second;

        if (size == 0)
        {
            Response(0);
        }
        else
        {
            Response(sum/size);
        }
    }

    return 0;
}

template <typename Compare>
void nth_element(int *first, int *nth, int *last, Compare comp)
{
    while (last - first > 1)
    {
        int *pivot_iter = first + (last - first) / 2;
        int pivot = *pivot_iter;

        // 将基准点移到末尾
        swap(*(last - 1), *pivot_iter);
        int *store = first;

        // 遍历范围，将小于基准点的元素放到左侧
        for (int *it = first; it < last - 1; ++it)
        {
            if (comp(*it, pivot))
            {
                swap(*it, *store);
                store++;
            }
        }

        // 基准点归位
        swap(*store, *(last - 1));

        // 根据 nth 的位置调整范围
        if (nth < store)
        {
            last = store;
        }
        else if (nth > store)
        {
            first = store + 1;
        }
        else
        {
            return;
        }
    }
}
```

