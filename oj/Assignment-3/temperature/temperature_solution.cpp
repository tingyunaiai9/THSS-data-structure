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
