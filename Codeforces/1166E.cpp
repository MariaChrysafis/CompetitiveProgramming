#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
template <typename T>
T readVal(){
    T n;
    cin >> n;
    return n;
}
template <typename T>
vector<T> readVector(T n){
    vector<T> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}
template <typename T>
void printVector(vector<T> vec){
    for(T x: vec){
        cout << x << " ";
    }
    cout << endl;
}
void solve() {
    int n = readVal<int>();
    int m = readVal<int>();
    vector<set<int>> dora(n);
    vector<set<int>> swiper(n);
    for (int i = 0; i < n; i++){
        int s = readVal<int>();
        for(int j = 0; j < s; j++){
            dora[i].insert(readVal<int>());
        }
        for(int j = 1; j <= m; j++){
            if(!dora[i].count(j)){
                swiper[i].insert(j);
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {
            if (std::includes(swiper[j].begin(), swiper[j].end(), dora[i].begin(), dora[i].end())){
                cout << "impossible";
                return;
            }
        }
    }
    cout << "possible";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
