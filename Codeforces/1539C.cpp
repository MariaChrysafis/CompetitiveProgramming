#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
bool comp(pair<long long,long long> p1, pair<long long,long long> p2){
    return p1.second < p2.second;
}
void print(vector<pair<long long,long long>> v){
    for(pair<int,int> p: v){
        cout << p.first << " " << p.second << endl;
    }
}
void solve(){
    int n;
    cin >> n;
    vector<pair<long long,long long>> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i].first >> arr[i].second;
    }
    sort(arr.begin(), arr.end(), comp);
    //print(arr);
    long long pntr1 = 0;
    long long pntr2 = arr.size() - 1;
    long long cur = 0;
    long long ans = 0;
    while(pntr1 < pntr2){
        if(arr[pntr1].second <= cur && pntr1 < arr.size()){
            cur += arr[pntr1].first;
            ans += arr[pntr1].first;
            arr[pntr1].first = 0;
            pntr1++;
            continue;
        }
        long long delta = min(arr[pntr1].second - cur, arr[pntr2].first);
        cur += delta;
        arr[pntr2].first -= delta;
        ans += 2 * delta;
        if(arr[pntr2].first == 0){
            pntr2--;
        }
    }
    //print(arr);
    //cout << ans << endl;
    //cout << arr[pntr1].first << endl;
    if(pntr1 == pntr2){
        if(cur + arr[pntr1].first < arr[pntr1].second ){
            ans += 2 * arr[pntr1].first;
        }else{
            int moves =  max(arr[pntr1].second - cur, 0ll);
            ans += 2 * arr[pntr1].first - (arr[pntr1].first) + moves;
        }
    }
    cout << ans << endl;
}
int main(){
    solve();
}
