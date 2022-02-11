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
int N;
int M;
struct modint {
    modint() : n(0) {}
    template <class T> modint(T n) { n %= M; if (n < 0) n += M; this->n = n; }
 
    modint & operator+=(const modint &r) { n += r.n; if (n >= M) n -= M; return *this; }
    modint & operator-=(const modint &r) { n -= r.n; if (n < 0) n += M; return *this; }
    modint & operator*=(const modint &r) { n = (int) ((long long) n * r.n % M); return *this; }
 
    modint & operator--() { if (--n == -1) n = M - 1; return *this; }
    modint & operator++() { if (++n == M) n = 0; return *this; }
    modint operator--(int) { modint t = *this; --*this; return t; }
    modint operator++(int) { modint t = *this; ++*this; return t; }
 
    modint operator-() const { return 0 - *this; }
    modint operator+() const { return *this; }
 
    modint pow(long long k = M - 2) const {
        modint f = *this, p = 1;
        while (k > 0) {
            if (k % 2 == 1) f *= p;
            p *= p, k /= 2;
        }
        return f;
    }
 
    int mod() const { return M; }
 
    friend modint operator+(modint l, const modint &r) { return l += r; }
    friend modint operator-(modint l, const modint &r) { return l -= r; }
    friend modint operator*(modint l, const modint &r) { return l *= r; }
    
    friend bool operator==(const modint &l, const modint &r) { return l.n == r.n; }
    friend bool operator!=(const modint &l, const modint &r) { return l.n != r.n; }
 
    friend ostream & operator<<(ostream &out, const modint &r) { return out << r.n; }
 
    int n;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    vector<vector<modint>> combo(N + 1);
    vector<modint> fact = {1};
    while (fact.size() != N + 1) {
    	fact.push_back(fact.back() * fact.size());
    }
    for (int i = 0; i <= N; i++) {
    	combo[i].assign(N + 1, 0);
    }
    for (int i = 0; i <= N; i++) {
    	for (int j = 0; j <= N; j++) {
    		if (i < j) {
    			combo[i][j] = 0;
    			continue;
    		}
    		if (j == 0) {
    			combo[i][j] = 1;
    			continue;
    		}
    		combo[i][j] = combo[i - 1][j - 1] + combo[i - 1][j ];
    	}
    }
    const int offset = N * (N - 1)/2;
    vector<vector<modint>> dp(N + 1);
    for (int i = 0; i < dp.size(); i++) {
    	dp[i].assign(N * N + 1, 0);
    }
    dp[1][offset] = 1;
    for (int n = 2; n <= N; n++) {
    	for (int k = 0; k < (int)dp[n].size(); k++) {
    		dp[n][k] = 0;
    		for (int x = - (n - 1); x <= n - 1; x++) {
    			if (k - x >= 0 && k - x < (int)dp[n - 1].size()) {
    				dp[n][k] += dp[n - 1][k - x] * (n - abs(x));
	    		}
    		}
    	}
    }
    vector<modint> ans;
    ans.assign(N * N + 1, 0);
    for (int len = 0; len <= N - 1; len++) {
    	for (int p = 1; p < N - len; p++) {
    		//for (int q = p + 1; q < N - len; q++) {
    			for (int inv = 0; inv < dp[N].size(); inv++) {
    				if (inv + p >= 0 && inv + p < dp[N].size()) {
    					ans[inv] = ans[inv] + dp[N - len - 1][inv + p] * combo[N][len] * fact[len] * (N - len - p);
    				}
    			}
    		//}
    	}
    }
    modint res = 0;
    for (int i = offset + 1; i < ans.size(); i++) {
    	res += ans[i];
    }
    cout << res << '\n';
}
