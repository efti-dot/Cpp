#include<bits/stdc++.h>
using namespace std;
int main()
{
    int prv = 0, pre = 1, trm, i, n;

    cout << " Input number of terms to display: ";
    cin >> n;
    cout << prv << " " << pre;

    for (i = 3; i <= n; i++)
    {
        trm = prv + pre;
        cout << " " << trm;
        prv = pre;
        pre = trm;
    }
    cout << endl;
}
