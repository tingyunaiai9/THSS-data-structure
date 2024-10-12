# Assignment-1 Report

## 1 Interview

### 1.1 题目分析

#### 1.1.1 解题思路

本题使用双向循环链表实现

插入时顺序遍历m个结点，插入结束后从当前位置开始倒序输出全链表

#### 1.1.2 复杂度分析

其中单次插入复杂度 $O(m)$ ，总时间复杂度 $O(mn)$

### 1.2 代码实现

```cpp
#include <cstdio>

template <typename T>
inline void SAFE_DELETE(T*& t)
{
	if (t)
	{
		delete t;
	}
	t = nullptr;
}

//双向循环链表节点模板类
template <typename T> struct ListNode
{
    T m_data;
    ListNode<T> *m_previous; // 指向前一个结点
    ListNode<T> *m_next;     // 指向后一个结点

public:
    ListNode() : m_previous(nullptr), m_next(nullptr) {}
    ListNode(const T &data, ListNode<T> *previous = nullptr, ListNode<T> *next = nullptr)
        : m_data(data), m_previous(previous), m_next(next) {}
    ~ListNode() {}
};

//双向循环链表模板类
template <typename T> class List
{
public:
    ListNode<T> *m_head;

public:
    List() : m_head(nullptr) {}
    ~List();

    // 插入新节点并返回指针
    ListNode<T>* mb_insertAsNextNode(ListNode<T> *p, const T &data);
};

template <typename T>
List<T>::~List()
{
    if(m_head == nullptr)
        return;

    ListNode<T> *p = m_head;
    ListNode<T> *q;
    do
    {
        q = p->m_next;
        p->m_previous = nullptr;
        SAFE_DELETE(p);
        p = q;
    }while(p != m_head);
}

template <typename T>
ListNode<T>* List<T>::mb_insertAsNextNode(ListNode<T> *p, const T &data)
{
    ListNode<T> *pNew = nullptr;

    // 双向链表空，插入第一个节点
    if (m_head == nullptr)
    {
        pNew = new ListNode<T>(data);
        if (pNew == nullptr)
            return nullptr;

        m_head = pNew;
        m_head->m_previous = m_head;
        m_head->m_next = m_head;
        return pNew;
    }

    // 双向链表非空，插入新节点
    if (p == nullptr)
        return nullptr;

    ListNode<T> *q = m_head;
    do
    {
        if (q == p)
        {
            pNew = new ListNode<T>(data);
            if (pNew == nullptr)
                return nullptr;

            pNew->m_previous = p;
            pNew->m_next = p->m_next;
            p->m_next->m_previous = pNew;
            p->m_next = pNew;
            return pNew;
        }
        q = q->m_next;
    }while(q != m_head);

    // 链表中不存在p节点
    return nullptr;
}

int main()
{
    int n, m;
    std::scanf("%d %d", &n, &m);

    List<int> interviewList;
    ListNode<int> *pCurrent = nullptr;

    int id = 0;
    // first person
    std::scanf("%d", &id);
    pCurrent = interviewList.mb_insertAsNextNode(nullptr, id);

    for (int i=1; i<n; i++)
    {
        std::scanf("%d", &id);
        for (int j=0; j<m-1; j++)
        {
            pCurrent = pCurrent->m_next;
        }
        pCurrent = interviewList.mb_insertAsNextNode(pCurrent, id);
    }

    for (int i=0; i<n; i++)
    {
        std::printf("%d ", pCurrent->m_data);
        pCurrent = pCurrent->m_previous;
    }

    return 0;
}
```

## 2 Train

### 2.1 题目分析

#### 2.1.1 解题思路

本题使用栈，为“栈混洗”问题

即在栈容量为 $m$ 的前提下，原序列 $\{1, 2, ..., n \}$ 是否能通过栈混洗，重排为指定序列 $\{a_1, a_2, ..., a_n \}$

程序中，遍历指定序列

* 当栈顶元素等于当前元素时，出栈，记录操作

* 当栈顶元素不等于当前元素且栈未满时，入栈，记录操作

* 栈满了则输出 No

#### 2.1.2 复杂度分析

对于指定序列仅遍历了一遍，总时间复杂度 $O(n)$

### 2.2 代码实现

```cpp
#include <cstdio>

#define MAX 1600001

int stack[MAX] = {0};
int target[MAX] = {0};

bool operation[2*MAX] = {0}; // 0: push, 1: pop

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &target[i]);
    }

    if (m == 0)
    {
        printf("No\n");
        return 0;
    }

    int i = 0;
    int top = 0;
    int targetIndex = 0;
    int operationIndex = 0;

    for (; targetIndex < n; targetIndex++)
    {
        while (top == 0 || stack[top] != target[targetIndex])
        {
            if (top >= m) // 下一个元素在栈第m+1位置
            {
                printf("No\n");
                return 0;
            }
            else // push
            {
                stack[++top] = ++i;
                operation[operationIndex++] = 0;
            }
        }

        // pop
        top--;
        operation[operationIndex++] = 1;
    }

    for (int i=0; i<operationIndex; i++)
    {
        if (operation[i] == 0)
            printf("push\n");
        else
            printf("pop\n");
    }
}
```

## 3 Light House

### 3.1 题目分析

#### 3.1.1 解题思路

本题使用归并排序，类似于求“逆序对”的解法

先将灯塔按 $x$ 坐标由小到大排序，再将灯塔按 $y$ 坐标由大到小排序

记录第二次排序中的“逆序对”个数，即满足 $x_1 < x_2$ 且 $y_1 < y_2$ 的灯塔对个数，即为所求

#### 3.1.2 复杂度分析

使用了两轮归并排序，总时间复杂度 $O(n\log n)$

### 3.2 代码实现

```cpp
#include <cstdio>

#define LEN 4000000

struct Point
{
    int x;
    int y;
};

Point points[LEN];
Point temp[LEN];

void mergeSortX(int left, int right);
void mergeByX(int left, int mid, int right);
long long mergeSortYCount(int left, int right);
long long mergeByYCount(int left, int mid, int right);

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    long long count = 0;
    mergeSortX(0, n);
    count = mergeSortYCount(0, n);

    printf("%lld\n", count);

    return 0;
}

void mergeSortX(int left, int right) // 左闭右开
{
    if (right - left < 2)
        return;

    int mid = (left + right) / 2;
    mergeSortX(left, mid);
    mergeSortX(mid, right);
    mergeByX(left, mid, right);
}

void mergeByX(int left, int mid, int right)
{
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right)
    {
        if (points[i].x < points[j].x)
            temp[k++] = points[i++];
        else
            temp[k++] = points[j++];
    }

    while (i < mid)
        temp[k++] = points[i++];

    while (j < right)
        temp[k++] = points[j++];

    for (int i=left; i<right; i++)
        points[i] = temp[i];
}

long long mergeSortYCount(int left, int right) // 左闭右开
{
    if (right - left < 2)
        return 0;

    int mid = (left + right) / 2;
    long long count = 0;
    count = mergeSortYCount(left, mid) + mergeSortYCount(mid, right);
    count += mergeByYCount(left, mid, right);

    return count;
}

long long mergeByYCount(int left, int mid, int right)
{
    int i = left;
    int j = mid;
    int k = left;
    long long count = 0;

    while (i < mid && j < right)
    {
        if (points[i].y > points[j].y)
            temp[k++] = points[i++];
        else
        {
            temp[k++] = points[j++];
            count += mid - i;
        }
    }

    while (i < mid)
        temp[k++] = points[i++];

    while (j < right)
        temp[k++] = points[j++];

    for (int i=left; i<right; i++)
        points[i] = temp[i];

    return count;
}
```

