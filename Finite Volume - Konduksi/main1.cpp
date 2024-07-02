#include <iostream>

using namespace std;

int main1()
{
    int a, b, c, d, i;

    a = 1;
    b = 2;
    d = 0;

    for (i = 0; i <= 10; i++)
    {
        c = a + b + d;

        cout << a << endl;
        cout << b << endl;
        cout << c << endl;
        cout << d << endl;
        cout << endl;


        d = c;
    }
return 0;
}


