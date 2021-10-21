#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
vector<int> prime_factor;
vector<int> distinct_pf;
vector<int> powr;
void solve() {
    long long c, d, x;
    cin >> c >> d >> x;
    vector<int> fact;
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            fact.push_back(i);
        }
    }
    int sz = fact.size();
    for (int i = 0; i < sz; i++) {
        fact.push_back(x/fact[i]);
    }
    if (fact.back() * fact.back() == x) {
        fact.pop_back();
    }
    int ans = 0;
    for (int g: fact) {
        if ((x/g + d) % c == 0) {
            ans += powr[distinct_pf[(x/g + d) /c]];
        }
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    powr.push_back(1);
    while(powr.size() != 20) {
        powr.push_back(2 * powr.back());
    }
    prime_factor.resize(((int)2e7 + 1));
    for (int i = 0; i < prime_factor.size(); i++) {
        prime_factor[i] = 0;
    }
    distinct_pf = prime_factor;
    for (int i = 2; i < prime_factor.size(); i++) {
        if (prime_factor[i] == 0) {
            prime_factor[i] = i;
            for (int j = 2 * i; j < prime_factor.size(); j += i) {
                prime_factor[j] = i;
            }
        }
    }
    for (long long i = 2; i < distinct_pf.size(); i++) {
        if (prime_factor[i] == i) {
            distinct_pf[i] = 1;
        } else {
            distinct_pf[i] = distinct_pf[i / prime_factor[i]] + !((long long)i % (prime_factor[i] * prime_factor[i]) == 0);
        }
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
