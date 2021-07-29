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
#include <array>
#include <iomanip>
 
#define ll long long
#define endl '\n'
 
using namespace std;
void solve(){
    double a, b;
    cin >> a >> b;
    cout << std::setprecision(30) << (a - b)/3 + b << endl;
}
 
int main() {
    solve();
}
