#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
class Intervals {
public:
    set<pair<int64_t,int64_t>> intervals;
    void print () {
        for (auto& p: intervals) {
            cout << p.first << " " << p.second << '\n';
        }
        cout << '\n';
    }
    pair<int64_t,int64_t> leftIntersect (pair<int64_t,int64_t> &p) {
        auto it = intervals.upper_bound({p.first + 1, -1});
        if (it == intervals.begin()) {
            return {-1, -1};
        }
        it--;
        pair<int64_t,int64_t> q = *it;
        if (q.second < p.first) {
            return {-1, -1};
        }
        return q;
    }
    pair<int64_t,int64_t> rightIntersect (pair<int64_t,int64_t> p) {
        auto it = intervals.upper_bound({p.second + 1, -1});
        if (it == intervals.begin()) {
            return {-1, -1};
        }
        it--;
        pair<int64_t,int64_t> q = *it;
        if (q.first > p.second || q.first < p.first) {
            return {-1, -1};
        }
        return q;
    }
    bool willChange (pair<int64_t,int64_t> p) {
        pair<int64_t,int64_t> q = leftIntersect(p);
        if (q.first < 0 && q.second < 0) {
            return true;
        }
        if (q.first <= p.first && q.second >= p.second) {
            return false;
        }
        return true;
    }
    pair<int64_t,int64_t> update_left (pair<int64_t,int64_t> p) {
        pair<int64_t,int64_t> q = leftIntersect(p);
        if (q.first == -1 && q.second == -1) {
            return p;
        }
        if (q.second < p.first) {
            return p;
        }
        intervals.erase(q);
        return {q.first, p.second};
    }
    pair<int64_t,int64_t> update_right (pair<int64_t,int64_t> p) {
        pair<int64_t,int64_t> q = rightIntersect(p);
        if (q.first == -1 && q.second == -1) {
            return p;
        }
        if (q.first > p.second) {
            return p;
        }
        intervals.erase(q);
        return {p.first, q.second};
    }
    void erase_in_between (pair<int64_t,int64_t> p) {
        auto it = intervals.lower_bound({p.first, -1});
        set<pair<int64_t,int64_t>> to_erase;
        while (it != intervals.end()) {
            if ((*it).second < p.second) {
                to_erase.insert(*it);
            } else {
                break;
            }
            it++;
        }
        for (auto& q: to_erase) {
            intervals.erase(q);
        }
    }
    void add_interval (pair<int64_t,int64_t> p) {
        if (!willChange(p)) {
            return;
        }
        erase_in_between(p);
        pair<int64_t,int64_t> new_p1 = update_right(update_left(p));
        intervals.insert(new_p1);
    }
};
int64_t gcd (int64_t a, int64_t b) {
    if (!a || !b) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    int64_t A, B;
    cin >> N >> A >> B;
    A /= gcd(A, B + 1);
    int64_t prod;
    if (A < 1e18/B) {
        prod = A * B;
    } else {
        prod = 1e18;
    }
    Intervals myInterval;
    for (int i = 0; i < N; i++) {
        int64_t x, y;
        cin >> x >> y;
        if (abs(y - x) >= prod) {
            myInterval.add_interval({0, prod - 1});
            continue;
        }
        x %= (prod), y %= (prod);
        if (x <= y) {
            myInterval.add_interval({x, y});
        } else {
            swap(x, y);
            myInterval.add_interval({0, x});
            myInterval.add_interval({y, prod - 1});
        }
    }
    int64_t ans = 0;
    for (auto& p: myInterval.intervals) {
        ans += p.second - p.first + 1;
    }
    cout << ans << '\n';
}
