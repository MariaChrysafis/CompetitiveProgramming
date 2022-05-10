#include <iostream>
#include <vector>
using namespace std;
int cost (char c1, char c2) {
    int a = abs(c1 - c2);
    return a;
}
int dif (string s1, string s2) {
    int ans = 0;
    for (int i = 0; i < s1.length(); i++) {
        ans += cost(s1[i], s2[i]);
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<string> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        int myMin = INT_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                myMin = min(myMin, dif(v[i], v[j]));
            }
        }
        cout << myMin << '\n';
    }
}
