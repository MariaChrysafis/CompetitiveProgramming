#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;
vector<int> times;
vector<int> distances = {1000};
int pntT, pntD;
double curPos = 0;
double curTime = 0;
int seen = 1;

void updateTime() {
    curPos = curPos + (times[pntT] - curTime) / (seen + 0.0);
    curTime = times[pntT];
    pntT++;
}

void updateDistance() {
    curTime += seen * (distances[pntD] - curPos);
    curPos = distances[pntD];
    pntD++;
}

int main() {
    freopen("slowdown.in", "r", stdin);
    freopen("slowdown.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        int x;
        cin >> x;
        if (c == 'T') times.push_back(x);
        else if (c == 'D') distances.push_back(x);
        else assert(false);
    }
    sort(times.begin(), times.end());
    sort(distances.begin(), distances.end());
    while (pntT < times.size() || pntD < distances.size()) {
        if (pntT == times.size()) {
            updateDistance();
        } else if (pntD == distances.size()) {
            updateTime();
        } else if (times[pntT] - curTime < (distances[pntD] - curPos) * seen) {
            updateTime();
        } else {
            updateDistance();
        }
        seen++;
        //cout << curTime << " " << curPos << " " << seen << endl;
    }
    if (curTime - floor(curTime) < 0.5) cout << setprecision(30) << floor(curTime);
    else cout << setprecision(30) << ceil(curTime);
}
