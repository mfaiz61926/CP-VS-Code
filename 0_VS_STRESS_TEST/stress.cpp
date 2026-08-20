#include <bits/stdc++.h>
using namespace std;

int main() {

    for(int test = 1; ; test++) {

        system("gen.exe > input.txt");

        system("main.exe < input.txt > out1.txt");

        system("brute.exe < input.txt > out2.txt");

        if(system("fc out1.txt out2.txt")) {

            cout << "Wrong Answer!\n";

            cout << "Test number: " << test << "\n";

            cout << "Input:\n";

            system("type input.txt");

            break;
        }

        cout << "Test " << test << " passed\n";
    }

    return 0;
}