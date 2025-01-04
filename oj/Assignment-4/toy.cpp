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
