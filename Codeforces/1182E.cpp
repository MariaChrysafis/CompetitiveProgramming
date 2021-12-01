#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
ll MOD = 1e9 + 7;
using namespace std;
struct Matrix {
    vector<vector<ll>> mat1;
    Matrix operator *(const Matrix& other) {
        vector<vector<ll>> mat2 = other.mat1;
        vector<vector<ll>> ans(mat1.size());
        for (int i = 0; i < ans.size(); i++) {
            ans[i].resize(mat2[0].size());
            for (int j = 0; j < ans[i].size(); j++) {
                ans[i][j] = 0;
                for (int k = 0; k < mat1[0].size(); k++) {
                    ans[i][j] += mat1[i][k] * mat2[k][j];
                    ans[i][j] %= (MOD - 1);
                }
            }
        }
        Matrix m;
        m.mat1 = ans;
        return m;
    }
    Matrix identity (int n) {
        Matrix ans;
        ans.mat1.resize(n);
        for (int i = 0; i < n; i++) {
            ans.mat1[i].resize(n);
            for (int j = 0; j < n; j++) {
                ans.mat1[i][j] = (i == j);
            }
        }
        return ans;
    }
    Matrix binPow (ll powr) {
        Matrix res = {mat1};
        Matrix ans = identity(mat1.size());
        while (powr > 0) {
            if (powr & 1) {
                ans = ans * res;
            }
            res = res * res;
            powr /= 2;
        }
        return ans;
    }
};
ll mult (ll x, ll y) {
    return (x * y) % MOD;
}
ll binPow (ll x, ll y) {
    ll res = x;
    ll ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans = ans * res;
            ans %= MOD;
        }
        res = res * res;
        res %= MOD;
        y /= 2;
    }
    return ans;
}
Matrix transition1 = {{{1, 1, 1}, {1, 0, 0}, {0, 1, 0}}};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, f1, f2, f3, c;
    cin >> n >> f1 >> f2 >> f3 >> c;
    Matrix base1 = {{{1}, {0}, {0}}};
    Matrix base2 = {{{0}, {1}, {0}}};
    Matrix base3 = {{{0}, {0}, {1}}};
    Matrix F = transition1.binPow(n - 1);
    Matrix F1 = F * base1;
    Matrix F2 = F * base2;
    Matrix F3 = F * base3;
    ll ans = 1;
    //cout << F3.mat1[2][0] << '\n';
    ans = mult(ans, binPow(f1, F3.mat1[2][0]));
    ans = mult(ans, binPow(f2, F2.mat1[2][0]));
    ans = mult(ans, binPow(f3, F1.mat1[2][0]));
    Matrix trans = {{{1,1,1,1,2}, {1,0,0,0,0},{0,1,0,0,0},{0,0,0,1,2},{0,0,0,0,1}}};
    Matrix sing = {{{0},{0},{0},{0},{1}}};
    Matrix res = trans.binPow(n - 1) * sing;
    ans = mult(ans, binPow(c,res.mat1[2][0]));
    cout << ans << '\n';
}
