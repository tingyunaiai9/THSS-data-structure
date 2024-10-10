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
