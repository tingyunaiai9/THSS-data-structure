#include <iostream>

using namespace std;

int main()
{
    double a, b, result;
    char op;

    cin >> a >> op >> b;

    switch(op)
    {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        default:
            result = 0;
            break;
    }

    cout << result << endl;

    return 0;
}
