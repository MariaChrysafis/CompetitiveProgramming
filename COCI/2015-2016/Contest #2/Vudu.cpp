#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;
struct BIT{
    int bit[(int)1e6 + 5];
    int pref(long long ind){
        int ans = 0;
        ind++;
        while(ind > 0){
            //cout << ind << " ";
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }
    int sum(long long l, long long r){
        if(l == 0){
            return pref(r);
        }
        return pref(r) - pref(l - 1);
    }
    void update(int ind, int val){
        ind++;
        while(ind < (int)1e6 + 5){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
};
struct Triple {
public:
    int64_t pref;
    int ind;
    int place = 0;
    Triple () {
 
    }
    Triple (int64_t pref, int ind) {
        this->pref = pref, this->ind = ind;
    }
};
bool cmp1 (Triple t1, Triple t2) {
    if (t1.pref == t2.pref) return (t1.ind < t2.ind);
    return (t1.pref < t2.pref);
}
bool cmp2 (Triple t1, Triple t2) {
    return (t1.ind < t2.ind);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; cin >> N;
    Triple pref[N + 1];
    pref[0] = Triple(0, 0);
    for (int i = 0; i < N; i++) {
        int64_t x; cin >> x;
        pref[i + 1].pref = pref[i].pref + x;
        pref[i + 1].ind = i + 1;
    }
    int64_t P; cin >> P;
    for (int i = 0; i <= N; i++) {
        pref[i].pref = pref[i].pref - P * i;
    }
    sort(pref, pref + N + 1, cmp1);
    for (int i = 0; i <= N; i++) {
        pref[i].place = i;
    }
    sort(pref, pref + N + 1, cmp2);
    BIT b;
    for (int i = 0; i <= (int)1e6; i++) {
        b.bit[i] = 0;
    }
    int64_t c = 0;
    for (int r = 0; r < N; r++) {
        b.update(pref[r].place + 1, 1);
        c += (int64_t)b.sum(0, pref[r + 1].place + 1);
    }
    cout << c;
}
