#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <stack>
#include <map>
#include <set>
using namespace std;
const long long INF = 1000000000000000000;
vector<long long> arr;
vector<long long> interval;
vector<long long> pref;
vector<pair<int,int>> pref_rep;
int find_first(long long l, long long r, long long x){
    if(l == r){
        return l;
    }
    //find first time element is greater or equal to x in pref
    long long m = (l + r)/2;
    if(pref[m] >= x){
        return find_first(l, m, x);
    }else{
        return find_first(m + 1, r, x);
    }
}
void print(vector<long long> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int q;
    cin >> q;
    arr.push_back(0);
    for(int i = 1; i <= n; i++){
        long long x;
        cin >> x;
        arr.push_back(x);
    }
    arr.push_back(INF);
    for(int i = 1; i < arr.size(); i++){
        interval.push_back(arr[i] - arr[i - 1] - 1);
    }
    //print(arr);
    //pref.push_back(0);
    pref.push_back(0);
    for(int i = 0; i < interval.size(); i++){
        pref.push_back(interval[i] + pref.back());
    }
    //print(interval);
    //print(pref);
    for(int i = 0; i < pref.size(); i++){
        pref_rep.push_back({i, i + 1});
    }
    while(q--){
        long long x;
        cin >> x;
        long long y = find_first(0, pref.size() - 1, x);
        long long delta = x - pref[y - 1];
        cout << arr[pref_rep[y].first - 1] +delta << endl;
    }
}
