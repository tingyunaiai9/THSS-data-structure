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
