#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
const int MOD = 1e9 + 7;
class Matrix {
public:
    vector<vector<int64_t>> v;
    void print () {
        for (int i = 0; i < v.size(); i++) {
            for (int j: v[i]) {
                cout << j << ' ';
            }
            cout << '\n';
        }
    }
    Matrix operator* (Matrix m1) const {
        Matrix ans(v);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                ans.v[i][j] = 0;
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    //cout << k << " " << j << " " << m1.v[k][j] << '\n';
                    ans.v[i][j] += (v[i][k] * m1.v[k][j]) % MOD;
                    ans.v[i][j] %= MOD;
                }
            }
        }
        return ans;
    }
    Matrix identity (int64_t n) {
        vector<vector<int64_t>> v(n);
        for (int i = 0; i < n; i++) {
            v[i].resize(n);
            for (int j = 0; j < n; j++) {
                v[i][j] = (i == j);
            }
        }
        return Matrix(v);
    }
    Matrix operator^ (int64_t x) {
        Matrix ans = identity(v.size());
        Matrix res = *this;
        while (x > 0) {
            if (x & 1) {
                ans = res * ans;
            }
            res = res * res;
            x /= 2;
        }
        return ans;
    }
    Matrix (vector<vector<int64_t>> v) {
        this->v = v;
    }
};
int64_t binPow (int64_t x, int y) {
    int64_t ans = 1;
    int64_t res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res; res %= MOD;
        y >>= 1;
    }
    return ans;
}
int64_t inv (int64_t x) {
    return binPow(x, MOD - 2);
}
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Matrix fib = Matrix({{1, 1}, {1, 0}});
    int64_t n;
    cin >> n;
    fib = fib ^ n;
    cout << fib.v[0][1];
}
