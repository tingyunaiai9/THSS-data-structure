#include "CList.h"

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
