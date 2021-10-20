#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#define ll int

using namespace std;

int gcd(int a, int b) {
    if (min(a,b) == 0) {
        return max(a,b);
    }
    return gcd(max(a,b) % min(a,b), min(a,b));
}
void print(vector<int> v) {
    cout << v.size() << endl;
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
int main() {
    int n;
    cin >> n;
    vector<int> pos;
    long long prod = 1;
    for (int i = 1; i <= n; i++) {
        if (gcd(i, n) == 1) {
            pos.push_back(i);
            prod *= i;
            prod %= n;
        }
    }
    if (prod == 1) {
        print(pos);
        return 0;
    }
    pos.pop_back();
    print(pos);
}
