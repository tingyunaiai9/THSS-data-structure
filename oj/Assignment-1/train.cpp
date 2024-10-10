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
