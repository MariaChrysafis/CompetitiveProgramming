#include <map>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int arr[n];
        map<int,int> myMap;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            myMap[arr[i]]++;
        }
        vector<int> s;
        for (auto& p: myMap) {
            if (p.second >= k) {
                s.push_back(p.first);
            }
        }
        if (s.empty()) {
            cout << "-1\n";
            continue;
        }
        if (s.size() == 1) {
            cout << s[0] << " " << s[0] << '\n';
            continue;
        }
        int cntr = 1;
        int m = 0;
        pair<int,int> p, cur;
        cur = make_pair(s[0], s[0]);
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1] + 1) {
                cntr++;
                cur.second++;
            } else {
                cntr = 1;
                cur = make_pair(s[i], s[i]);
            }
            if (cntr >= m) {
                p = cur;
                m = cntr;
            }
        }
        cout << p.first << " " << p.second << '\n';

    }
}
