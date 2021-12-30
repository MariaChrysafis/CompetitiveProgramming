#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string A, B;
    cin >> A >> B;
    while (A.length() < B.length()) {
        A = "0" + A;
    }
    while (B.length() < A.length()) {
        B = "0" + B;
    }
    for (int i = 0; i < A.length(); i++) {
        if ((A[i] - '0') + (B[i] - '0') >= 10) {
            cout << "Hard\n";
            return 0;
        }
    }
    cout << "Easy\n";
}
