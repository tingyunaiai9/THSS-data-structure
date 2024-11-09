#include <cstdio>

#define LEN 4000000
// #define LEN 5

int pre[LEN], in[LEN], post[LEN];

int search(int *array, int x, int left, int right); // 在无序array的[left, right)区间内查找x，返回下标

void build_tree(int in_left, int in_right,
                int pre_left, int pre_right,
                int post_left, int post_right); // 左闭右开

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &pre[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &post[i]);

    build_tree(0, n, 0, n, 0, n);
    for (int i = 0; i < n; i++)
        printf("%d ", in[i]);

    return 0;
}

int search(int *array, int x, int left, int right)
{
    for (int i = left; i < right; i++)
    {
        if (array[i] == x)
            return i;
    }

    return -1;
}

void build_tree(int in_left, int in_right,
                int pre_left, int pre_right,
                int post_left, int post_right)
{
    if (in_left >= in_right)
        return;

    if (in_left == in_right-1)
    {
        in[in_left] = pre[pre_left];
        return;
    }

    int root = pre[pre_left];
    int left = pre[pre_left + 1];
    int right = post[post_right - 2];

    int left_index = search(post, left, post_left, post_right);
    // 左子树长度 left_index - post_left + 1
    build_tree(in_left, in_left + left_index - post_left + 1,
               pre_left + 1, pre_left + left_index - post_left + 2,
               post_left, left_index + 1);

    in[in_left + left_index - post_left + 1] = root;

    int right_index = pre_left + left_index - post_left + 2;
    // 右子树长度 pre_right - right_index
    build_tree(in_left + left_index - post_left + 2, in_right,
               right_index, pre_right,
               left_index + 1, post_right - 1);
}
