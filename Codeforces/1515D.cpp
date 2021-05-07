#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
void print(vector<int> v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}
vector<int> read(vector<int> v){
    vector<int> vec(v.size());
    for(int i = 0; i < v.size(); i++){
        cin >> vec[i];
    }
    return vec;
}
map<int,int> myMap(vector<int> v){
    map<int,int> m;
    for(int i: v) m[i]++;
    return m;
}
vector<int> construct(map<int,int> m){
    vector<int> v;
    for(pair<int,int> p: m){
        int x = p.second;
        while(x--){
            v.push_back(p.first);
        }
    }
    return v;
}
void solve(){
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> left(l), right(r);
    left = read(left), right = read(right);
    map<int,int> ml = myMap(left);
    map<int,int> mr = myMap(right);
    for(pair<int,int> p: ml){
        int i = p.first;
        int myMin = min(mr[i], ml[i]);
        ml[i] -= myMin;
        mr[i] -= myMin;
    }
    //cout << mr[2] << " " << ml[2] << endl;
    left = construct(ml), right = construct(mr);
    int ans = 0;
    if(left.size() > right.size()){
        swap(left, right);
    }
    //left.size() <= right.size()
    mr.clear(), ml.clear();
    mr = myMap(right);
    l = left.size(), r = right.size();
    for(pair<int,int> p: mr){
        if(l == r) break;
        //int x = p.second;
        //cout << p.first << " "<< p.second << endl;
        for(int i = 0; i < p.second; i += 2){
            if(i == p.second - 1) break;
            //cout << p.first << " " << p.second << endl;
            ans ++;
            r -= 2;
            mr[p.first] -= 2;
            if(l == r) break;
        }
    }
    right = construct(mr);
    //ans += abs((int)left.size() - (int)right.size());
    //print(left);
    //print(right);
    cout << ans + abs((int)left.size() - (int)right.size())/2 + (left.size() + right.size())/2  << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
