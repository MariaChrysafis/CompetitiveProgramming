#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

struct segmentTreePoint {
    vector<int> addLater;

    vector<int> fenwick;

    void update (int index, int delta) {
        for (; index <= fenwick.size() - 1; index += (index & -index))
            fenwick[index] += delta;
    }

    int query (int index) {
        long long result = 0;
        for (; index > 0; index -= (index & -index))
            result += fenwick[index];
        return result;
    }

    void range_update (int left, int right, int delta) {
        update(left, delta);
        update(right + 1, -delta);
    }

    void resz (int n) {
        fenwick.resize(n + 1);
    }

};

vector<segmentTreePoint> seg;
vector<int> oc;
vector<int> indices;
int sq;

int findFirstSmaller (int x) {
    int l = 0;
    int r = indices.size() - 1;
    while (l != r) {
        int m = (l + r + 1)/2;
        if (indices[m] <= x) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int get (int l, int r, int x) {
    if (x < 0) return 0;
    if (x == 0) return (oc[x] >= l && oc[x] <= r);
    int x1 = findFirstSmaller(x);
    int ans = seg[x1].query(r + 1) - seg[x1].query(l);
    for (int i = indices[x1] + 1; i <= x; i++) {
        if (oc[i] >= l && oc[i] <= r) {
            ans++;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    int arr[N];
    oc.resize(N);
    for (int i = 0; i < N; i++) {
        arr[i] = i;
        oc[i] = i;
    }
    sq = sqrt(N);
    for (int i = 0; i <= sq; i++) {
        indices.push_back(sq * i);
    }
    indices.push_back(N - 1);
    seg.resize(indices.size());
    for (int i = 0; i < indices.size(); i++) {
        seg[i].resz(N + 1);
        int cntr = 0;
        for (int j = 0; j < N; j++) {
            cntr += (j <= indices[i]);
            seg[i].range_update(j + 1, j + 1, cntr);
        }
    }
    ll inv = 0;
    while (Q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (l > r) {
            swap(l , r);
        }
        if (l == r) {
            cout << inv << '\n';
            continue;
        }
        int left = min(arr[l], arr[r]) + 1;
        int right = max(arr[l], arr[r]) - 1;
        int ans = get(l + 1, r - 1, right) - get(l + 1, r - 1, left - 1);
        if (arr[l] < arr[r]) inv += 2 * ans;
        else inv -= 2 * ans;
        if (arr[l] < arr[r]) inv++;
        else inv--;
        for (int i = 0; i < indices.size(); i++) {
            int ind = indices[i];
            if (ind >= arr[l] && ind >= arr[r]) continue;
            if (ind < arr[l] && ind < arr[r]) continue;
            if (ind >= arr[l]) {
                seg[i].range_update(l + 1, r, -1);
            }
            if (ind >= arr[r]) {
                seg[i].range_update(l + 1, r, +1);
            }
        }
        swap(arr[l], arr[r]);
        swap(oc[arr[l]], oc[arr[r]]);
        cout << inv << '\n';
    }
}
