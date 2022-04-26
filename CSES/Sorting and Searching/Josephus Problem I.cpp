#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
 
using namespace __gnu_pbds;
using namespace std;
 
typedef
tree<
        int,
        null_type,
        less<int>,
        rb_tree_tag,
        tree_order_statistics_node_update>
        ordered_set;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ordered_set s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        s.insert(i);
    }
    int ind = 0;
    for (int i = 0; i < n; i++) {
        ind += 1; ind %= (s.size());
        cout << *s.find_by_order(ind) + 1 << ' ';
        s.erase(s.find_by_order(ind));
    }
}
