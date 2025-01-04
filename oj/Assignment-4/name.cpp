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
