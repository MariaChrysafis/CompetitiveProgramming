#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <set>
#include <functional>
#include <queue>
using namespace std;
struct Frac {
    int64_t numerator;
    int64_t denominator;
    Frac (int64_t x, int64_t y) {
        this->numerator = x, this->denominator = y;
    }
};

bool operator < (const Frac& f1, const Frac& f2) {
    return (f1.numerator * f2.denominator < f1.denominator * f2.numerator);
}

bool operator > (const Frac& f1, const Frac& f2) {
    return (f1.numerator * f2.denominator > f1.denominator * f2.numerator);
}


bool operator == (const Frac& f1, const Frac& f2) {
    return (f1.numerator * f2.denominator == f1.denominator * f2.numerator);
}

bool operator <= (const Frac& f1, const Frac& f2) {
    return (f1 < f2 || f1 == f2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int64_t a[n];
    int64_t pref_a[n + 1];
    int64_t b[n];
    int64_t pref_b[n + 1];
    pref_a[0] = pref_b[0] = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref_a[i + 1] = pref_a[i] + a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        pref_b[i + 1] = pref_b[i] + b[i];
    }
    int64_t dp[n][n];
    for (int i_a = 0; i_a < n; i_a++) {
        for (int i_b = 0; i_b < n; i_b++) {
            dp[i_a][i_b] = (pref_a[i_a + 1] * (i_b + 1) <= pref_b[i_b + 1] * (i_a + 1));
        }
    }
    const int MOD = 1e9 + 7;
    auto add = [&] (int64_t x, int64_t y) {
        if ((x + y) >= MOD) return x + y - MOD;
        else return x + y;
    };
    for (int i_a = 0; i_a < n; i_a++) {
        vector<pair<Frac,int64_t>> left;
        for (int p_a = 0; p_a < i_a; p_a++) {
            left.emplace_back(Frac(pref_a[i_a + 1] - pref_a[p_a + 1], i_a - p_a), p_a);
        }
        sort(left.begin(), left.end());
        int64_t pref[left.size() + 1][n];
        for (int i = 0; i <= left.size(); i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0) {
                    pref[i][j] = 0;
                } else {
                    pref[i][j] = add(pref[i - 1][j], dp[left[i - 1].second][j]);
                }
            }
        }
        for (int i_b = 0; i_b < n; i_b++) {
            for (int p_b = 0; p_b < i_b; p_b++) {
                int ll = 0;
                int rr = (int)left.size() - 1;
                if (left.empty()) {
                    continue;
                }
                auto f = Frac(pref_b[i_b + 1] - pref_b[p_b + 1], i_b - p_b);
                while (ll < rr) {
                    int mm = (ll + rr + 1)/2;
                    if (left[mm].first <= f) {
                        ll = mm;
                    } else {
                        rr = mm - 1;
                    }
                }
                if (left[ll].first > f) {
                    continue;
                }
                dp[i_a][i_b] = add(dp[i_a][i_b], pref[ll + 1][p_b]);
                /*
                for (int i = 0; i <= ll; i++) {
                    auto l = left[i];
                    dp[i_a][i_b] = add(dp[i_a][i_b], dp[l.second][p_b]);
                }
                 */
            }
        }
    }
    cout << dp[n - 1][n - 1] << '\n';
}
