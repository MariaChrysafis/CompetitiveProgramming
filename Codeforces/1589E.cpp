#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long

using namespace std;
using namespace __gnu_pbds;

typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> order_set;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC target("avx2")


struct segmentTree {
   vector <vector<long long>> dp;
   vector<long long> arr;
   const long long INF = 1e12;

   long long minI(ll left, ll length) {
       //length is actually log2(length)
       if (left + (1 << length) - 1 >= arr.size()) return -INF;
       if (dp[left][length] != -1) {
           return dp[left][length];
       }
       if (length == 0) {
           dp[left][length] = arr[left];
           return dp[left][length];
       }
       ll l = minI(left, length - 1);
       ll r = minI(left + (1 << (length - 1)), length - 1);
       dp[left][length] = min(l, r);
       return dp[left][length];
   }

   long long query(ll l, ll r) {
       ll length = log2(r - l + 1);
       return min(dp[l][length], dp[r - pow(2, length) + 1][length]);
   }

   void read() {
       ll n = arr.size();
       dp.resize(n);
       for (ll i = 0; i < n; i++) {
           dp[i].resize(log2(n) + 2); //buffer
       }
       for (ll i = 0; i < n; i++) {
           for (ll j = 0; j < dp[i].size(); j++) {
               dp[i][j] = -1;
           }
       }
       for (ll i = 0; i < n; i++) {
           for (ll j = 0; j < dp[i].size(); j++) {
               dp[i][j] = minI(i, j);
           }
       }
   }
};

ll howMany(vector<ll> &v, ll up) {
   if (v.back() <= up) {
       return v.size();
   }
   if (v[0] > up) {
       return 0;
   }
   //how many elements are in the range [0, up]
   //find the last element which is <= up
   ll l = 0;
   ll r = v.size() - 1;
   while (l < r) {
       ll m = (l + r + 1) / 2;
       if (v[m] <= up) {
           l = m;
       } else {
           r = m - 1;
       }
   }
   return l + 1;
}

ll in_rng(vector<ll> &v, ll l, ll r) {
   if (v.empty()) {
       return 0;
   }
   return howMany(v, r) - howMany(v, l - 1);
}

void solver() {
   ll n;
   cin >> n;
   vector<ll> v(n);
   for (ll i = 0; i < n; i++) {
       cin >> v[i];
   }
   segmentTree stOdd, stEven;
   stOdd.arr.resize((n + 1)/2), stEven.arr.resize((n + 1)/2);
   order_set mySet;
   ll cur[n];
   cur[0] = v[0];
   for (ll i = 1; i < n; i++) {
       cur[i] = v[i] - cur[i - 1];
   }
   for (ll i = 0; i < n; i++) {
       mySet.insert(cur[i]);
       mySet.insert(-cur[i]);
   }
   mySet.insert(0);
   vector<ll> myMapEven[mySet.size()], myMapOdd[mySet.size()];
   for (ll i = 0; i < n; i += 2) {
       myMapEven[mySet.order_of_key(cur[i])].push_back(i);
   }
   for (ll i = 1; i < n; i += 2) {
       myMapOdd[mySet.order_of_key(cur[i])].push_back(i);
   }
   for (ll i = 0; i < n; i++) {
       if (i % 2 == 1) {
           stOdd.arr[i/2] = cur[i];
       } else {
           stEven.arr[i/2] = cur[i];
       }
   }
   stOdd.read();
   stEven.read();
   ll cntr = 0;
   for (ll i = 0; i < n; i++) {
       ll l = i;
       ll r = n - 1;
       ll des;
       if (i == 0) des = 0;
       else des = cur[i - 1];
       ll cur = des;
       if (i % 2 == 1) {
           cur = -cur;
       }
       while (l < r) {
           ll m = (l + r) / 2;
           if (stOdd.query(i / 2, m / 2) - cur < 0 || stEven.query(i / 2, m / 2) + cur < 0) {
               r = m;
           } else {
               l = m + 1;
           }
       }
       if (i % 2 == 1) {
           cntr += in_rng(myMapOdd[mySet.order_of_key(-des)], i, l);
           cntr += in_rng(myMapEven[mySet.order_of_key(des)], i, l);
       } else {
           cntr += in_rng(myMapOdd[mySet.order_of_key(des)], i, l);
           cntr += in_rng(myMapEven[mySet.order_of_key(-des)], i, l);
       }
   }
   cout << cntr << '\n';
}


int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   ll t;
   cin >> t;
   while (t--) {
       solver();
   }
}

