#include <iostream>
#include <vector>
using namespace std;
int gcd(int x, int y){
    if(min(x, y) == 0) return max(x, y);
    return gcd(max(x,y) % min(x, y), min(x,y));
}
int f(int n){
    for(int i = 2; i < n; i++){
        if(gcd(n, i) == 1){
            return i;
        }
    }
}
void print(vector<vector<int>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            cout << v[i][j] + 1 << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void solve(int n){
    if(n == 1){
        cout << 1 << endl;
        return;
    }
    if(n == 2){
        cout << -1 << endl;
        return;
    }
    if(n == 3){
        cout << "2 9 7" << endl;
        cout << "4 6 3" << endl;
        cout << "1 8 5" << endl;
        return;
    }
    if(n == 4){
        cout << "3 7 11 15" << endl;
        cout << "1 5 9 13" << endl;
        cout << "4 8 12 16" << endl;
        cout << "2 6 10 14" << endl;
        return;
    }
    if(n == 6){
        cout << "5 11 17 23 29 35" << endl;
        cout << "3 9 15 21 27 33" << endl;
        cout << "1 7 13 19 25 31" << endl;
        cout << "4 10 16 22 28 34" << endl;
        cout << "2 8 14 20 26 32" << endl;
        cout << "6 12 18 24 30 36" << endl;
        return;
    }
    int x = f(n);
    //cout << x << endl;
    int strt = 0;
    vector<vector<int>> v(n);
    for(int i = 0; i < n; i++){
        //all the numbers that are x modulo n
        for(int j = 0; j < n; j++){
            int ans = n * j + strt;
            v[i].push_back(ans);
            //cout << ans % (n * n) + 1 << " ";
        }
        //cout << endl;
        strt += x;
        strt %= n;
    }
    print(v);
}
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        solve(n);
    }
}
