#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <iomanip>
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<double> x(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> r[i];
    }
    stack<int> indices;
    indices.push(0);
    for (int i = 1; i < n; i++) {
        while(!indices.empty()) {
            int j = indices.top();
            double val = ((x[i] - x[j]) * (x[i] - x[j])) / (4.0 * r[j]);
            r[i] = min(r[i], val);
            if (r[i] >= r[j]) {
                indices.pop();
            } else {
                break;
            }
        }
        indices.push(i);
    }
    for (double d: r) {
        cout << setprecision(30) << d << "\n";
    }
}
