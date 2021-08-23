#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;
void print(vector<long long> v){
    for(long long i: v) cout << i << " ";
        cout << endl;
}
void print(vector<vector<long long>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
vector<vector<long long>> transpose(vector<vector<long long>> v){
    vector<vector<long long>> vec(v[0].size());
    for(int i = 0; i < v[0].size(); i++){
        for(int j = 0; j < v.size(); j++){
            vec[i].push_back(v[j][i]);
        }
    }
    return vec;
}
vector<long long> geom;
vector<long long> difBase(long long n){
    vector<long long> v;
    long dig = 0;
    for(int i = 0; i < geom.size(); i++){
        if(n >= geom[i]){
            dig = i;
        }
    }
    //if(n == 256) cout << geom[dig] << endl;
    n -= geom[dig];
    long long dum = n;
    dig++;
    while(dig--){
        v.push_back(dum % 4);
        dum /= 4;
    }
    v.push_back(1);
    reverse(v.begin(), v.end());
    return v;
}
vector<long long> powr2;
long long convertBinary(vector<long long> v){
    reverse(v.begin(), v.end());
    long long ans = 0;
    for(int i = 0; i < v.size(); i++){
        ans += powr2[i] * v[i];
    }
    return ans;
}
vector<vector<long long>> construct(vector<long long> v){
    vector<vector<long long>> ans(3);
    for(long long i: v){
        if(i == 0){
            ans[0].push_back(0), ans[0].push_back(0);
            ans[1].push_back(0), ans[1].push_back(0);
            ans[2].push_back(0), ans[2].push_back(0);
        }else if(i == 1){
            ans[0].push_back(0), ans[0].push_back(1);
            ans[1].push_back(1), ans[1].push_back(0);
            ans[2].push_back(1), ans[2].push_back(1);
        }else if(i == 2){
            ans[0].push_back(1), ans[0].push_back(0);
            ans[1].push_back(1), ans[1].push_back(1);
            ans[2].push_back(0), ans[2].push_back(1);
        }else if(i == 3){
            ans[0].push_back(1), ans[0].push_back(1);
            ans[1].push_back(0), ans[1].push_back(1);
            ans[2].push_back(1), ans[2].push_back(0);
        }
    }
    return ans;
}
void solve(long long n){
    long long orig = n;
    n = (n + 2)/3 - 1;
    vector<vector<long long>> vec = construct(difBase(n));
    vector<long long> v;
    for(int i = 0; i < 3; i++){
        v.push_back(convertBinary(vec[i]));
    }
    cout << v[(orig + 2) % 3] << endl;
}
int main(){
    int t;
    cin >> t;
    geom.resize(28);
    geom[0] = 1;
    vector<long long> powr;
    powr.push_back(1);
    powr2.push_back(1);
    while(powr.size() != 28){
        powr.push_back(powr.back() * 4);
    }
    while(powr2.size() != 56){
        powr2.push_back(powr2.back() * 2);
    }
    for(int i = 1; i < geom.size(); i++){
        geom[i] = geom[i - 1] + powr[i];
    }
    //return 0;
    while(t--){
        long long n;
        cin >> n;
        solve(n);
    }
}
