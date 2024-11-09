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

    int count_a = 0, count_b = 0;
    int count_c_dealed = 0;

    if (num[0] <= num[1]) // A <= B
    {
        int k = num[1] - num[0];
        int M = num[2];

        for (int i=0; i<n; i++)
        {
            if (balls[i] == 'A')
                count_a++;
            else if (balls[i] == 'B')
                count_b++;
            else // C
            {
                if (count_c_dealed < k)
                {
                    count_c_dealed++;
                    balls[i] = 'A';
                    count_a++;
                }
                else if (count_c_dealed < k + (M-k)/2)
                {
                    count_c_dealed++;
                    balls[i] = 'A';
                    count_a++;
                }
                else
                {
                    count_c_dealed++;
                    if (count_c_dealed >= (k + (M-k)/2 + (M-k)%2))
                    {
                        balls[i] = 'B';
                        count_b++;
                    }
                }

            }

            if (count_b > count_a)
            {
                printf("False\n");
                return 0;
            }
        }
    }
    else // A > B
    {
        int k = num[0] - num[1];
        int M = num[2];

        for (int i=0; i<n; i++)
        {
            if (balls[i] == 'A')
                count_a++;
            else if (balls[i] == 'B')
                count_b++;
            else // C
            {
                if (count_c_dealed < (M-k)/2)
                {
                    count_c_dealed++;
                    balls[i] = 'A';
                    count_a++;
                }
                else if (count_c_dealed < M-k)
                {
                    count_c_dealed++;
                    if (count_c_dealed > (M-k)/2 + (M-k)%2)
                    {
                        balls[i] = 'B';
                        count_b++;
                    }
                }
                else
                {
                    count_c_dealed++;
                    balls[i] = 'B';
                    count_b++;
                }
            }

            if (count_b > count_a)
            {
                printf("False\n");
                return 0;
            }
        }
    }

    printf("True\n");

    return 0;
}
