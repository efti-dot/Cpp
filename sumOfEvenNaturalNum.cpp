#include <bits/stdc++.h>
using namespace std;
int main()
{
    int i, n, sum = 0;
    cout << " Input number of terms: ";
    cin >> n;

    cout << "\n The even numbers are: ";

    for (i = 1; i <= n; i++)
    {
        cout << 2 * i << " ";
        sum += 2 * i;
    }

    cout << "\n The Sum of even Natural Numbers up to " << n << " terms: " << sum << endl;
}
