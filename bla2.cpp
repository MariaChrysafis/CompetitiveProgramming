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
#include <stack>

using namespace std;
typedef long long ll;
double binPow (double a, int powr) {
    double res = a;
    double ans = 1;
    while (powr > 0) {
        if (powr & 1) {
            ans *= res;
        }
        res *= res;
        powr /= 2;
    }
    return ans;
}

int main() {
    int N, K;
    cin >> N >> K;
    N--;
    double combo[N + 1][N + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (j == 0) combo[i][j] = 1;
            else if (i < j) combo[i][j] = 0;
            else combo[i][j] = combo[i - 1][j] + combo[i - 1][j - 1];
        }
    }
    double p[N + 1];
    //p[0] = 0;
    for (int i = 0; i <= N; i++) {
        double prev = 0;
        if (i != 0) prev = p[i - 1];
        p[i] = prev + combo[N][i] * binPow(0.5, N);
    }
    double e[N + 1];
    for (int i = 0; i <= N; i++) {
        double tot = 0;
        for (int j = i; j <= N; j++) {
            tot += combo[N][j];
        }
        double num = 0;
        for (int j = i; j <= N; j++) {
            num += combo[N][j] * j;
        }
        e[i] = num/tot;
    }
    double myMax = 0;
    for (int x = 0; x <= N; x++) {
        double ans = binPow(p[x - 1], K - 1) * e[0];
        double res = (-binPow(p[x - 1], K - 1) + 1) * e[x];
        ans += res;
        myMax = max(myMax, ans + 1);
    }
    cout << setprecision(30) << myMax;
}
