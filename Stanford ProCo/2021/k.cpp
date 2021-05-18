#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<int,int>> solve(vector<pair<char,int>> v){
    vector<pair<int,int>> pref;
    //(white, black)
    pref.push_back(make_pair(0, 0));
    for(int i = 0; i < v.size(); i++){
        if(v[i].first == 'W'){
            pref.push_back(pref.back());
            pref.back().first += v[i].second;
        }else{
            pref.push_back(pref.back());
            pref.back().second += v[i].second;
        }
    }
    return pref;
}
int main(){
    int n;
    cin >> n;
    int k;
    cin >> k;
    string s;
    cin >> s;
    vector<pair<char,int>> v;
    v.push_back(make_pair(s[0], 1));
    for(int i = 1; i < s.length(); i++){
        if(v.back().first == s[i]){
            v[v.size() - 1].second++;
        }else{
            v.push_back(make_pair(s[i],1));
        }
    }
    //return 0;
    vector<pair<int,int>> pref = solve(v);
    reverse(v.begin(), v.end());
    vector<pair<int,int>> suf = solve(v);
    reverse(suf.begin(), suf.end());;
    int arr[n + 1];
    for(int i = 0; i <= n; i++) arr[i] = 0;
    for(int i = 0; i < suf.size(); i++) arr[suf[i].second] = max(arr[suf[i].second], suf[i].first);
    for(int i = 1; i < n; i++){
        arr[i] = max(arr[i - 1], arr[i]);
    }
    //for(int i: arr) cout << i << " ";
    int myMax = 0;
    for(int i = 0; i < pref.size(); i++){
        int curBlack = pref[i].second;
        if(curBlack > k) continue;
        int curWhit = arr[k - curBlack] + pref[i].first;
        //////cout << curWhit << " ";
        myMax = max(myMax, curWhit);
    }
    cout << myMax << endl;
}
