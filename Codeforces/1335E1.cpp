#include <iostream>
#include <vector>
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
    }
    vector<vector<int> > oc(26);
    int best = 0;
    for (int i = 0; i < 26; i++) {
        oc[i].resize(n);
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                oc[i][j] = (arr[j] == i);
            } else {
                oc[i][j] = oc[i][j - 1] + (arr[j] == i);
            }
        }
        best = max(best, oc[i][n - 1]);
    }
    if(n == 1){
        cout << 1 << endl;
        return;
    }
    for (int outside = 0; outside < 26; outside++) {
        for (int pref = 0; pref < n; pref++) {
            for (int suf = pref + 1; suf < n; suf++) {
                int left = oc[outside][pref];
                int right = oc[outside][n - 1] - oc[outside][suf - 1];
                int myMax = 0;
                for (int j = 0; j < 26; j++) {
                    myMax = max(oc[j][suf - 1] - oc[j][pref], myMax);
                }
                best = max(best, min(left, right) * 2 + myMax);
            }
        }
    }
    cout << best << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
