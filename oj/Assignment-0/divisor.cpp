#include <iostream>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;

    int r = 1;
    while (r != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }

    cout << a << endl;

    return 0;
}
