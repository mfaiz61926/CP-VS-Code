#include <bits/stdc++.h>
using namespace std;


int main() {

    srand(time(0));

    int n = rand() % 10 + 1;

    cout << n << "\n";

    for(int i = 0; i < n; i++) {

        int x = rand() % 21 - 10;

        cout << x << " ";
    }
    cout << "\n";
    return 0;
}