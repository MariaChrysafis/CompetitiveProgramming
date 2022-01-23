#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    string a[N], b[M];
    map<string,int> oc;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> b[i];
        oc[b[i]]++;
    }
    for (int i = 0; i < N; i++) {
        if (oc[a[i]]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
