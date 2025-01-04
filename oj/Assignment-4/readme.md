# Assignment-4 Report

## 1 task

### 1.1 题目分析

本题使用最小堆，重复调用插入-上滤、删除-下滤的函数，完成题目要求任务

时间复杂度 $O((m+n) \log n)$

### 1.2 代码实现

```cpp
#include <stdio.h>
#include <cstring>
#include <math.h>

using namespace std;

#define MAXN 4000005

struct Node
{
    long long priority;
    char name[10];
};

bool isSmallerNode(Node a, Node b)
{
    if (a.priority < b.priority)
    {
        return true;
    }
    else if (a.priority > b.priority)
    {
        return false;
    }
    else
    {
        return strcmp(a.name, b.name) < 0;
    }
}

// 最小堆
class MyHeap
{
public:
    Node m_heap[MAXN];
    int m_size;

public:
    MyHeap()
    {
        m_size = 0;
    }

    bool isEmpty()
    {
        return m_size == 0;
    }

    void insert(Node node)
    {
        m_heap[m_size] = node;
        m_size++;

        percolateUp(m_size - 1, node);
    }

    void percolateUp(int index, Node node)
    {
        int parentIndex = (index - 1) / 2;

        while (index > 0 && isSmallerNode(node, m_heap[parentIndex]))
        {
            m_heap[index] = m_heap[parentIndex];
            index = parentIndex;
            parentIndex = (parentIndex - 1) / 2;
        }

        m_heap[index] = node;
    }

    Node getMin()
    {
        return m_heap[0];
    }

    void deleteMin()
    {
        m_size--;

        Node value = m_heap[m_size];
        m_heap[m_size] = m_heap[0];
        m_heap[0] = value;

        percolateDown(0, value);
    }

    void percolateDown(int index, Node node)
    {
        int minChildIndex = 2 * (index + 1); // 目标节点右子节点
        bool goDown = true;

        while (goDown && minChildIndex < m_size)
        {
            goDown = false;

            if (isSmallerNode(m_heap[minChildIndex - 1], m_heap[minChildIndex]))
            {
                minChildIndex--;
            }

            if (isSmallerNode(m_heap[minChildIndex], node))
            {
                m_heap[index] = m_heap[minChildIndex];
                index = minChildIndex;
                minChildIndex = 2 * (minChildIndex + 1);
                goDown = true;
            }
        }
        if (minChildIndex == m_size)
        {
            if (isSmallerNode(m_heap[minChildIndex - 1], node))
            {
                m_heap[index] = m_heap[minChildIndex - 1];
                index = minChildIndex - 1;
            }
        }

        m_heap[index] = node;
    }
};

MyHeap heap;

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    Node tmp_node;
    for(int i=0; i<n; i++)
    {
        scanf("%lld %s", &tmp_node.priority, tmp_node.name);
        heap.insert(tmp_node);
    }

    long long max_priority = 1ll << 31;
    for (int i=0; i<m; i++)
    {
        if (heap.isEmpty())
            break;

        Node minNode = heap.getMin();
        printf("%s\n", minNode.name);
        heap.deleteMin();

        if(minNode.priority < max_priority)
        {
            minNode.priority = minNode.priority * 2;
            heap.insert(minNode);
        }
    }

    return 0;
}
```

## 2 name

### 2.1 题目分析

本题使用哈希算法，建立映射，同时记录是否重复

时间复杂度 $O(n)$

### 2.2 代码实现

```cpp
#include <stdio.h>
#include <cstring>

const int PRIME = 180181;
const int BASE = 31;
const int MAXN = 1e6;

struct Node
{
    char name[45];
    bool isRepeated;

    Node* next;
};

int get_hash_value(char* name)
{
    int len = strlen(name);
    int hash_value = 0;

    for (int i = 0; i < len; i++)
    {
        hash_value = (hash_value * BASE + name[i] - 'a') % PRIME;
    }

    return hash_value;
}

class hashTable
{
public:
    Node* m_table[PRIME];

public:
    void insert(char* name)
    {
        int hash_value = get_hash_value(name);

        Node* newNode = new Node();
        strcpy(newNode->name, name);
        newNode->isRepeated = false;
        newNode->next = NULL;

        if (m_table[hash_value] == NULL)
        {
            m_table[hash_value] = newNode;
        }
        else
        {
            Node* current = m_table[hash_value];
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    int query(char* name)
    {
        int hash_value = get_hash_value(name);

        for (Node* current = m_table[hash_value]; current != NULL; current = current->next)
        {
            if (strcmp(current->name, name) == 0)
            {
                if (current->isRepeated == false) // 第一次重复
                {
                    current->isRepeated = true;
                    return 1;
                }
                else // 已经重复过了
                {
                    return 2;
                }
            }
        }

        return 0; // 没有重复
    }
};

hashTable hash_table;

int main()
{
    int n;
    scanf("%d", &n);
    char name[45];

    for (int i=0; i<n; i++)
    {
        scanf("%s", name);
        int result = hash_table.query(name);
        if (result == 0) // 没有重复，插入
        {
            hash_table.insert(name);
        }
        else if (result == 1) // 第一次重复，输出
        {
            printf("%s\n", name);
        }
    }

    return 0;
}
```

## 3 toy

### 3.1 题目分析

本题从初始状态开始，进行 bfs 搜索，记录每个状态所需步数

在输出时直接调用初始计算结果即可

使用康托展开建立哈希索引

时间复杂度 $O(n + 8!)$

### 3.2 代码实现

```cpp
#include <stdio.h>
#include <cstring>

const int TOTALSTATES = 40320; // 8! = 40320
const int MAXN = 50000;

int answer[MAXN];
int factorial[8] = {1, 1, 2, 6, 24, 120, 720, 5040};

struct State
{
    int num[8];
};

int cantor_expansion(State state)
{
    int cantor_value = 0;
    for (int i = 0; i < 8; ++i)
    {
        int count = 0;
        for (int j = i + 1; j < 8; ++j)
        {
            if (state.num[j] < state.num[i])
            ++count;
        }
        cantor_value += count * factorial[7 - i];
    }
    return cantor_value;
}

State cantor_reduction(int num)
{
    State state;
    bool vis[8] = {0};
    for (int i = 0; i < 8; ++i)
    {
        int count = num / factorial[7 - i];
        num %= factorial[7 - i];
        for (int j = 0; j < 8; ++j)
        {
            if (!vis[j])
            {
                if (count == 0)
                {
                state.num[i] = j, vis[j] = true;
                break;
                }
                --count;
            }
        }
    }
    return state;
}

class Queue
{
public:
    int m_queue[MAXN];
    int m_front, m_rear;

public:
    Queue()
    {
        m_front = 0;
        m_rear = 0;
    }

    void push(int x)
    {
        m_queue[m_rear++] = x;
        m_rear %= MAXN;
    }

    void pop()
    {
        m_front++;
        m_front %= MAXN;
    }

    int front()
    {
        return m_queue[m_front];
    }

    bool empty()
    {
        return m_front == m_rear;
    }
};

Queue queue;

int transform_a(int value)
{
    State old_state = cantor_reduction(value);

    State new_state;
    for (int i=0; i<8; i++)
    {
        new_state.num[i] = old_state.num[7-i];
    }

    return cantor_expansion(new_state);
}

int transform_b(int value)
{
    State old_state = cantor_reduction(value);

    State new_state;
    new_state.num[0] = old_state.num[1];
    new_state.num[1] = old_state.num[2];
    new_state.num[2] = old_state.num[3];
    new_state.num[3] = old_state.num[0];
    new_state.num[7] = old_state.num[6];
    new_state.num[6] = old_state.num[5];
    new_state.num[5] = old_state.num[4];
    new_state.num[4] = old_state.num[7];

    return cantor_expansion(new_state);
}

int transform_c(int value)
{
    State old_state = cantor_reduction(value);

    State new_state = old_state;
    new_state.num[1] = old_state.num[2];
    new_state.num[2] = old_state.num[5];
    new_state.num[5] = old_state.num[6];
    new_state.num[6] = old_state.num[1];

    return cantor_expansion(new_state);
}

void bfs()
{
    queue.push(0);
    answer[0] = 0;

    while (!queue.empty())
    {
        int value = queue.front();
        queue.pop();

        int a = transform_a(value);
        int b = transform_b(value);
        int c = transform_c(value);

        if (answer[a] == -1)
        {
            answer[a] = answer[value] + 1;
            queue.push(a);
        }
        if (answer[b] == -1)
        {
            answer[b] = answer[value] + 1;
            queue.push(b);
        }
        if (answer[c] == -1)
        {
            answer[c] = answer[value] + 1;
            queue.push(c);
        }
    }
}

int main()
{
    memset(answer, -1, sizeof(answer));
    bfs();

    int n;
    scanf("%d", &n);

    State state;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<8; j++)
        {
            scanf("%d", &state.num[j]);
        }

        int value = cantor_expansion(state);
        // printf("%d\n", value);
        printf("%d\n", answer[value]);
    }

    return 0;
}
```

