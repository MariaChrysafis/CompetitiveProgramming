#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

string sorted(string s) {
    sort(s.begin(), s.end());
    return s;
}

void print (vector<pair<int,int>> vec) {
    cout << vec.size() << '\n';
    for (pair<int,int> p: vec) {
        cout << p.first + 1 << " " << p.second + 1 << '\n';
    }
    cout << '\n';
}

void print (vector<vector<char>> v) {
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[0].size(); j++) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

struct triple {
    int x, y, z;
};

bool solve () {
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;
    vector<vector<char>> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> vec[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(vec[i][j] == '.') continue;
            int ans = 0;
            for(int cntr = 1; cntr < n * m; cntr++) {
                if (i - cntr < 0 || j + cntr >= m || j - cntr < 0 ) break;
                if(vec[i - cntr][j + cntr] != '.' && vec[i - cntr][j - cntr] != '.') {
                    ans++;
                } else {
                    break;
                }
            }
            //cout << i << " " << j << " " << ans << endl;
            if(ans >= k) {
                for(int cntr = 0; cntr < n * m; cntr++) {
                    if (i - cntr < 0 || j + cntr >= m || j - cntr < 0 ) break;
                    if(vec[i - cntr][j + cntr] != '.' && vec[i - cntr][j - cntr] != '.') {
                        vec[i - cntr][j - cntr] = 'M';
                        vec[i - cntr][j + cntr] = 'M';
                    } else {
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[0].size(); j++) {
            if(vec[i][j] == '*') return false;
        }
    }
    //print(vec);
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }

}
