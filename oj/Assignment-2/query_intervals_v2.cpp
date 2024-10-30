#include <cstdio>

#define MAX 10000001

int number[MAX] = {0};

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int x;
    for (int i=0; i<n; i++)
    {
        scanf("%d", &x);
        number[x]++;
    }

    for (int i=1; i<MAX; i++)
    {
        number[i] += number[i-1]; // number[i]记录的是<=i的数的个数
    }

    int range_left, range_right;
    for (int i=0; i<m; i++)
    {
        scanf("%d %d", &range_left, &range_right);
        if(range_left > 0)
            printf("%d\n", number[range_right] - number[range_left-1]);
        else
            printf("%d\n", number[range_right]);
    }

    return 0;
}
