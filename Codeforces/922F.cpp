#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

using namespace std;

int get_random (ordered_set& s) {
    int x = rand() % s.size();
    return *s.find_by_order(x);
}

void myerase(ordered_set &t, int v){
    int rank = t.order_of_key(v);
    ordered_set::iterator it = t.find_by_order(rank); 
    t.erase(it);
}

vector<int> factors (int x) {
    vector<int> v;
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            v.push_back(i);
            if (i * i != x) v.push_back(x/i);
        }
    }
    return v;
}

ordered_set unused;
ordered_set used;
const int MAX = 3e5 + 1;
vector<long long> oc(MAX);
long long cnt = 0;

void add (int x) {
    myerase(unused,x);
    used.insert(x);
    oc[x]++;
    for (int i: factors(x)) {
        cnt += (x != i && oc[i]); 
    }
    for (int i = 2 * x; i < MAX; i += x) {
        cnt += oc[i];
    }
}

void sub (int x) {
    myerase(used,x);
    unused.insert(x);
    oc[x]--;
    for (int i: factors(x)) {
        cnt -= (x != i && oc[i]);
    }
    for (int i = 2 * x; i < MAX; i += x) {
        cnt -= oc[i];
    }
}

int main() {
    int N, K;
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        unused.insert(i);
    }
    int t = 400000;
    while (t--) {
        if (unused.empty() && cnt < K) {
            cout << "No\n";
            return 0;
        }
        if (cnt == K) {
            cout << "Yes\n";
            cout << used.size() << '\n';
            for (int i: used) {
                cout << i << ' ';
            }
            cout << '\n';
            return 0;
        }
        if (cnt > K) {
            sub(get_random(used));
        } else if (cnt < K) {
            add(get_random(unused));
        }
    }
    cout << "No" << '\n';
}
