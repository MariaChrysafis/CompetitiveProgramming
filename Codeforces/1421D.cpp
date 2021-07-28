#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
#define ll long long
 
using namespace std;
void print(vector<long long> v){
    for(long long i: v) cout << i << " ";
    cout << endl;
}
struct coord{
    long long x, y;
};
coord operator+(coord a, coord b){
    return {a.x + b.x, a.y + b.y};
}
coord operator-(coord a, coord b){
    return {a.x - b.x, a.y - b.y};
}
bool operator==(coord a, coord b){
    return ((a.x == b.x) && (a.y == b.y));
}
vector<coord> v;
vector<long long> arr(6);
long long solver(coord c){
    if(c.x == 0){
        if(c.y > 0){
            return arr[1] * c.y;
        }else{
            return -arr[4] * c.y;
        }
    }else{
        if(c.x > 0){
            return arr[5] * c.x;
        }else{
            return -arr[2] * c.x;
        }
    }
}
void solve() {
    v.push_back({1, 1});
    v.push_back({0, 1});
    v.push_back({-1, 0});
    v.push_back({-1, -1});
    v.push_back({0, -1});
    v.push_back({1, 0});
    long long x, y;
    cin >> x >> y;
    coord cur = {x, y};
    for(int i = 0; i < 6; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < 6; k++){
                if(v[i] + v[j] == v[k]){
                    arr[k] = min(arr[k], arr[i] + arr[j]);
                }
            }
        }
    }
    //print(arr);
    long long ans = 0;
    if(x > 0){
        long long pos1 = arr[0] * x + solver(cur-(coord){x, x});
        long long pos2 = arr[5] * x + solver(cur - (coord){x, 0});
        ans = min(pos1, pos2);
    }else if(x < 0){
        long long pos1 = -arr[3] * x + solver(cur - (coord){x, x});
        long long pos2 = -arr[2] * x + solver(cur - (coord){x, 0});
        ans = min(pos1, pos2);
    }else{
        ans = solver(cur);
    }
    if(y > 0){
        long long pos2 = arr[0] * y + solver(cur - (coord){y, y});
        long long pos1 = arr[1] * y + solver(cur - (coord){0 , y});
        ans = min(min(pos1, pos2), ans);
    }else if(y < 0){
        long long pos2 = -arr[3] * y + solver(cur - (coord){y, y});
        long long pos1 = -arr[4] * y + solver(cur - (coord){0 , y});
        ans = min(min(pos1, pos2), ans);
    }
    cout << ans << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
