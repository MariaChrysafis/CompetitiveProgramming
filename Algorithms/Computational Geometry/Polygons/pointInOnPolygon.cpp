#include <iostream>
#include <vector>

#define ll long long
using namespace std;

struct point {
    ll x, y;

    bool operator==(point &p) {
        return (p.x == x && p.y == y);
    }
};

struct triangle {
    point a;
    point b;
    point c;

    ll signedArea() {
        return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    }
};

bool innerPoint(point q, point a, point b) {
    if (a.y > b.y) {
        swap(a, b);
    }
    triangle t = {a, b, q};
    return (a.y <= q.y) && (b.y > q.y) && (t.signedArea() > 0);
}

bool between(point a, point b, point c) {
    triangle t = {a, b, c};
    if (t.signedArea() != 0) {
        return false;
    }
    bool a1 = (b.x <= max(a.x, c.x) && b.y <= max(a.y, c.y));
    bool a2 = (b.x >= min(a.x, c.x) && b.y >= min(a.y, c.y));
    return a1 && a2;
}

struct polygon {
    vector<point> points;

    bool pointInPolygon(point &p) {
        //check if p lies inside the polygon
        int n = points.size();
        int cntr = 0;
        for (int i = 0; i < n; i++) {
            int cur = i;
            int nxt = (i + 1) % n;
            if (points[cur].y == points[nxt].y) {
                continue;
            }
            if (points[cur].y > points[nxt].y) {
                swap(cur, nxt);
            }
            if (innerPoint(p, points[cur], points[nxt])) {
                cntr++;
            }
        }
        return (cntr % 2 == 1);
    }

    bool pointOnPolygon(point &p) {
        int n = points.size();
        for (int i = 0; i < n; i++) {
            int cur = i;
            int nxt = (i + 1) % n;
            if (between(points[cur], p, points[nxt])) {
                return true;
            }
        }
        return false;
    }
};

void solve() {
    int n;
    cin >> n;
    int m;
    cin >> m;
    polygon poly;
    for (int i = 0; i < n; i++) {
        point p;
        cin >> p.x >> p.y;
        poly.points.push_back(p);
    }
    for (int i = 0; i < m; i++) {
        point p;
        cin >> p.x >> p.y;
        if (poly.pointOnPolygon(p)) {
            cout << "BOUNDARY" << endl;
            continue;
        }
        if (poly.pointInPolygon(p)) {
            cout << "INSIDE" << endl;
            continue;
        }
        cout << "OUTSIDE" << endl;
    }
}

int main() {
    solve();
}
