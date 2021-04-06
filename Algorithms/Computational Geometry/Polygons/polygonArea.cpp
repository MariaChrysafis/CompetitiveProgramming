#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int64_t x;
    int64_t y;

    bool operator==(Point &p) {
        return (p.x == x && p.y == y);
    }
};

struct Triangle {
    Point a;
    Point b;
    Point c;

    int64_t signedArea() {
        return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    }
};

bool innerPoint(Point q, Point a, Point b) {
    if (a.y > b.y) {
        swap(a, b);
    }
    Triangle t = {a, b, q};
    return (a.y <= q.y) && (b.y > q.y) && (t.signedArea() > 0);
}

bool between(Point a, Point b, Point c) {
    Triangle triangle = {a, b, c};
    if (triangle.signedArea() != 0) {
        return false;
    }
    bool a1 = (b.x <= max(a.x, c.x) && b.y <= max(a.y, c.y));
    bool a2 = (b.x >= min(a.x, c.x) && b.y >= min(a.y, c.y));
    return a1 && a2;
}

struct Polygon {
    vector<Point> points;

    bool pointInPolygon(Point &p) {
        //check if p lies inside the Polygon
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

    bool pointOnPolygon(Point &p) {
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

    int64_t area() {
        int n = points.size();
        int64_t sum = 0;
        for (int i = 0; i < n - 1; i++) {
            sum += points[i].x * points[i + 1].y;
        }
        for (int i = 0; i < n - 1; i++) {
            sum -= points[i].y * points[i + 1].x;
        }
        sum += points[n - 1].x * points[0].y;
        sum -= points[0].x * points[n - 1].y;
        return sum;
    }
};

void solve() {
    int n;
    cin >> n;
    Polygon polygon;
    for (int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;
        polygon.points.push_back(p);
    }
    cout << abs(polygon.area()) << endl;
}

int main() {
    solve();
}
