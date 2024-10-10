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
