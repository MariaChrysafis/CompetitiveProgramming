#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;
//vector<int> v = {1, 2, 5, 4, 5, 7};
pair<int,int> query1(int i, int j){
    //return make_pair(v[i] & v[j], v[i] | v[j]);
    cout << "and " << i + 1 << " " << j + 1<< endl;
    int x;
    cin >> x;
    cout << "or " << i + 1<< " " << j + 1 << endl;
    int y;
    cin >> y;
    return {x, y};
}
int convert(vector<bool> v){
    int ans = 0;
    for(int i = 0; i < v.size(); i++){
        ans += v[i] * pow(2, i);
    }
    return ans;
}
int main(int argc, const char * argv[]) {
    long long n;
    cin >> n;
    string s = "";
    while(n > 0){
        if(n % 2 == 0){
            n /= 2;
            s += 'B';
        }else{
            n--;
            s += 'A';
        }
    }
    reverse(s.begin(), s.end());
    cout << s << endl;
}
