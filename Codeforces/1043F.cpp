/*
     * Observations:
     * 1) We can fix a prime and then find the cost if we make the gcd divisible by that prime
     * 2) If a prime occurs frequently, then it's probably a good idea to use it
     * 3) cnt[p] -> the number of elements which are divisible p, or can be made divisible by p using at most 1 operation (1 mod p, 0 mod p, -1 mod p)
     * 4) cnt[p] < cnt[2] in order for us to consider it
*/
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
set<int> to_set (vector<int> v) {
    set<int> s;
    for (int i: v) {
        s.insert(i);
    }
    return s;
}
vector<int> remove_extra (vector<int> v) {
    set<int> s = to_set(v);
    vector<int> ans;
    for (int i: s) {
        ans.push_back(i);
    }
    return ans;
}
const int MAX = 3e5;
int gcd (int a, int b) {
    if (!a || !b) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
int reduce (int x) {
    int val = x;
    for (int i = 2; i <= sqrt(x); i++) {
        if (val % (i * i) == 0) {
            while (val % (i * i) == 0) {
                val /= i;
            }
        }
    }
    if (x != 1) {
        assert(val != 1);
    }
    return val;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        v[i] = reduce(v[i]);
    }
    v = remove_extra(v);
    vector<int> oc;
    oc.assign(MAX + 1, 0);
    for (int i = 0; i < v.size(); i++) {
        oc[v[i]] = i + 1;
    }
    for (int i: v) {
        if (i == -1) {
            continue;
        }
        for (int j = 2 * i; j <= MAX; j += i) {
            if (oc[j] >= 1) {
                v[oc[j] - 1] = -1;
            }
        }
    }
    vector<int> new_v;
    for (int i: v) {
        if (i != -1) {
            new_v.push_back(i);
        }
    }
    v = new_v;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (gcd(v[i], v[j]) == 1) {
                cout << 2;
                return 0;
            }
        }
    }
    int g = 0;
    for (int i = 0; i < v.size(); i++) {
        g = gcd(g, v[i]);
    }
    if (g != 1) {
        cout << -1;
        return 0;
    }
    if (v.size() >= 20) {
        cout << 3;
        return 0;
    }
    int myMin = v.size();
    for (int i = 0; i < (1 << v.size()); i++) {
        int g = 0;
        for (int j = 0; j < v.size(); j++) {
            if (i & (1 << j)) {
                g = gcd(g, v[j]);
            }
        }
        if (g == 1) {
            myMin = min(myMin, __builtin_popcount(i));
        }
    }
    cout << myMin;

}
