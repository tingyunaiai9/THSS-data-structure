#include <cstdio>

#define MAX 500001

int number[MAX];
int temp[MAX];

void mergeSort(int left, int right); // 左闭右开
void merge(int left, int mid, int right);

int search_geq(int x, int left, int right); // 左闭右开，返回number中第一个>=x的下标
int search(int x, int left, int right); // 左闭右开，返回number中第一个>x的下标

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i=0; i<n; i++)
    {
        scanf("%d", &number[i]);
    }
    mergeSort(0, n);

    int range_left, range_right;
    for (int i=0; i<m; i++)
    {
        scanf("%d %d", &range_left, &range_right);
        printf("%d\n", search(range_right, 0, n) - search_geq(range_left, 0, n));
    }

    return 0;
}

void mergeSort(int left, int right)
{
    if (right - left < 2)
        return;

    int mid = (left + right) / 2;
    mergeSort(left, mid);
    mergeSort(mid, right);
    merge(left, mid, right);
}

void merge(int left, int mid, int right)
{
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right)
    {
        if (number[i] < number[j])
            temp[k++] = number[i++];
        else
            temp[k++] = number[j++];
    }

    while (i < mid)
        temp[k++] = number[i++];
    while (j < right)
        temp[k++] = number[j++];

    for (int i = left; i < right; i++)
        number[i] = temp[i];
}

int search_geq(int x, int left, int right)
{
    int mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        if (number[mid] < x)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int search(int x, int left, int right)
{
    int mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        if (number[mid] <= x)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}
