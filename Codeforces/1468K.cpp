#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
long long MOD = 1e9 + 7;
vector<long long> fact;
struct coord{
    int x;
    int y;
    coord operator+(coord c){
        return {this->x + c.x, this->y + c.y};
    }
    coord operator-(coord c){
        return {this->x - c.x, this->y - c.y};
    }
    bool operator<(coord c) const{
        if(this->x == c.x) return (this-> y < c.y);
        return (this-> x < c.x);
    }
};
map<char,coord> directions;
void solve() {
    string s;
    cin >> s;
    directions['R'] = {1, 0};
    directions['L'] = {-1, 0};
    directions['U'] = {0, 1};
    directions['D'] = {0, -1};
    coord dum = {0, 0};
    map<coord, set<int>> myMap; //maps a coordinate to when it occurs
    vector<coord> v;
    for(int i = 0; i < s.length(); i++){
        dum = dum + directions[s[i]];
        v.push_back(dum);
        myMap[dum].insert(i);
    }
    for(coord c: v){
        if(c.x == c.y && c.x == 0) continue;
        //c is where we place the obstacle
        coord cur = {c.x, c.y};
        coord offset = {0, 0};
        int earliestIndex = -1;
        while(!myMap[cur].empty()){
            if(myMap[cur].upper_bound(earliestIndex) == myMap[cur].end()){
                break;
            }
            earliestIndex = *myMap[cur].upper_bound(earliestIndex);
            cur = cur + directions[s[earliestIndex]];
            offset = offset - directions[s[earliestIndex]];
        }
        /*
        cout << "cur: " << cur.x << " " << cur.y << endl;
        cout << "offset: " << offset.x << " " << offset.y << endl;
        cout << "original obstacle: " << c.x << " " << c.y << endl;
        cout << "v: " << v.back().x << " " << v.back().y << endl;
        cout << "------" << endl;
         */
        if(offset.x + v.back().x == 0 && offset.y + v.back().y == 0){
            cout << c.x << " " << c.y << '\n';
            return;
        }
        //cout << offset.x << " " << offset.y << " " << v.back().x << " " << v.back().y << endl;
    }
    cout << "0 0\n";
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
