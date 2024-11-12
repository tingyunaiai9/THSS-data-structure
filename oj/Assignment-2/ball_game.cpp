#include <cstdio>

#define LEN 10000

char balls[LEN];

int main()
{
    int n;
    scanf("%d", &n);

    int num[3] = {0}; // 0-A 1-B 2-C

    for (int i=0; i<n; i++)
    {
        scanf(" %c", &balls[i]);
        num[(int)(balls[i] - 'A')]++;
    }

    if (num[0] <= num[1]) // A <= B
    {
        int k = num[1] - num[0];
        int M = num[2];

        if (k > M)
        {
            printf("False\n");
            return 0;
        }

        int count_c_dealed = 0;
        for (int i=0; count_c_dealed < k + (M-k)/2; i++)
        {
            if (balls[i] == 'C')
            {
                balls[i] = 'A';
                count_c_dealed++;
            }
        }
        count_c_dealed = 0;
        for (int i=n-1; count_c_dealed < (M-k)/2; i--)
        {
            if (balls[i] == 'C')
            {
                balls[i] = 'B';
                count_c_dealed++;
            }
        }
    }
    else // A>B
    {
        int k = num[0] - num[1];
        int M = num[2];

        if (k > M)
        {
            printf("False\n");
            return 0;
        }

        int count_c_dealed = 0;
        for (int i=n-1; count_c_dealed < k + (M-k)/2; i--)
        {
            if (balls[i] == 'C')
            {
                balls[i] = 'B';
                count_c_dealed++;
            }
        }
        count_c_dealed = 0;
        for (int i=0; count_c_dealed < (M-k)/2; i++)
        {
            if (balls[i] == 'C')
            {
                balls[i] = 'A';
                count_c_dealed++;
            }
        }
    }

    int count_a = 0, count_b = 0;
    for (int i=0; i<n; i++)
    {
        if (balls[i] == 'A')
        {
            count_a++;
        }
        else if (balls[i] == 'B')
        {
            count_b++;
        }

        if (count_b > count_a)
        {
            printf("False\n");
            return 0;
        }
    }

    printf("True\n");

    return 0;
}
