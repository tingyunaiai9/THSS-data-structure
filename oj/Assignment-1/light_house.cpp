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
