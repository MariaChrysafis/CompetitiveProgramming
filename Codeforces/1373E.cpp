#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <set>
#define ll long long
using namespace std;
int C (int n) {
    return n * (n + 1)/2;
}
string comp (ll n) {
    if (n == 9) {
        return "18";
    }
    //minimum integer with sum of digits of n
    if (n == 0) {
        return "";
    }
    string s = "";
    int sum = n;
    while (sum >= 1) {
        if (sum <= 9) {
            s += ('0' + sum);
            sum = 0;
            continue;
        } else if (sum <= 17) {
            s += '8';
            sum -= 8;
        } else {
            s += '9';
            sum -= 9;
        }
    }
    //cout << s << endl;
    sort(s.begin(), s.end());
    if (s.back() != '9') {
        return s;
    }
    if (s.back() == '9' && n % 9 == 0) {
        s.pop_back();
        s.push_back('1');
        s.push_back('8');
    }
    sort(s.begin(), s.end());
    vector<char> digits;
    for (char c: s) if (c != '9') digits.push_back(c);
    if (digits.size() == 1) {
        reverse(s.begin(), s.end());
        return s;
    }
    map<char,int> oc;
    for (char c: s) oc[c]++;
    //cout << oc['9'] << endl;
    if (digits.size() == 2) {
        string str;
        str += s[0];
        while (oc['9']--) str += '9';
        str += s[1];
        return str;
    }
    return s;
}
int sum_of_digits (ll x) {
    string s = to_string(x);
    int ans = 0;
    for (char c: s) {
        ans += c - '0';
    }
    return ans;
}
bool valid (ll x, ll n, ll k) {
    int sum = 0;
    for (int i = 0; i <= k; i++) {
        sum += sum_of_digits(x + i);
    }
    return (sum == n);
}
void solve (ll n, ll k) {
    if (k > n) {
        cout << "-1\n";
        return;
    }
    ll myMin = LLONG_MAX;
    if (n - (k + 1) * k/2 >= 0 && (n - (k + 1) * k/2) % (k + 1) == 0) {
        myMin = (n - (k + 1) * k/2) / (k + 1);
        if (!valid(myMin, n, k)) {
            myMin = LLONG_MAX;
        }
    }
    for (int i = 0; i <= k; i++) {
        //at x + i contains some number of trailing nines
        for (int trail = 1; trail <= 17; trail++) {
            if (n - 9 * trail < 0) {
                continue;
            }
            //(k + 1) f(x) - C(i + 1,2) + C(k - i,2) - trail * 9 * (k - i) = n
            ll ans = trail * 9 * (k - i) + n + C(i) - C(k - i);
            if (ans % (k + 1) != 0) {
                continue;
            }
            ans /= (k + 1);
            //we want a sum of digits of ans and trail trailing digits
            if (ans - 9 * trail < 0) {
                continue;
            }
            string pos = comp(ans - 9 * trail);
            for (int j = 0; j < trail; j++) {
                pos += '9';
            }
            ll val = stoll(pos);
            val -= i;
            if (!valid(val, n, k)) {
                continue;
            }
            myMin = min(myMin, val);
        }
    }
    if (myMin == LLONG_MAX) {
        cout << "-1\n";
        return;
    }
    cout << myMin << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        solve(n, k);
    }
}
