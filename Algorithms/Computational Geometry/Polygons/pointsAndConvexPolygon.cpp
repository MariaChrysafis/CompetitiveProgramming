#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (min(a, b) == 0) return max(a, b);
    return gcd(max(a, b) % min(a, b), min(a, b));
}

struct Point {
    int64_t x;
    int64_t y;

    bool operator==(Point &p) {
        return (p.x == x && p.y == y);
    }

    Point operator-(Point &p) {
        return {x - p.x, y - p.y};
    }

    Point operator+(Point &p) {
        return {p.x + x, p.y + y};
    }

    int64_t cross(const Point &p) {
        return x * p.y - y * p.x;
    }

    int64_t cross(Point a, Point b) {
        return (a - *this).cross(b - *this);
    }

    int64_t magnitude() {
        Point p = *this;
        return p.x * p.x + p.y * p.y;
    }

    void print() {
        cout << x << " " << y << endl;
    }

    void read() {
        cin >> x >> y;
    }
};

struct Line {
    Point p1;
    Point p2;

    int64_t latticePointsOnLine() {
        p1 = p1 - p2;
        p1.x = abs(p1.x);
        p1.y = abs(p1.y);
        return gcd(p1.x, p1.y);
    }

    bool onSegment(Point p) {
        Point a = p1;
        Point c = p2;
        Point b = p;
        if (b.cross(b, c) != 0) {
            return false;
        }
        bool a1 = (b.x <= max(a.x, c.x) && b.y <= max(a.y, c.y));
        bool a2 = (b.x >= min(a.x, c.x) && b.y >= min(a.y, c.y));
        return a1 && a2;
    }
};

struct Triangle {
    Point a;
    Point b;
    Point c;

    int64_t signedArea() {
        return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    }

    bool inTriangle(Point p) {
        //determine if p is in the triangle
        int64_t s1 = signedArea();
        Triangle t1 = {a, b, p};
        Triangle t2 = {b, c, p};
        Triangle t3 = {a, c, p};
        return (abs(s1) == abs(t1.signedArea()) + abs(t2.signedArea()) + abs(t3.signedArea()));
    }

    bool onTriangle(Point p) {
        Line l1 = {a, b};
        Line l2 = {a, c};
        Line l3 = {b, c};
        return l1.onSegment(p) || l2.onSegment(p) || l3.onSegment(p);
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
    vector<Point> originPoints;

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

    int64_t boundaryLattice() {
        int n = points.size();
        int64_t cntr = 0;
        for (int i = 0; i < n; i++) {
            int cur = i;
            int nxt = (i + 1) % n;
            Line l = {points[cur], points[nxt]};
            cntr += l.latticePointsOnLine();
        }
        return cntr;
    }

    int64_t latticePoints() {
        return (abs(area()) - boundaryLattice()) / 2 + 1;
    }

    void fill() {
        int n = points.size();
        int pos = 0;
        for (int i = 1; i < n; i++) {
            Point cur = points[i];
            Point nxt = points[pos];
            if ((cur.x < nxt.x || (cur.x == nxt.x && cur.y < nxt.y))) {
                pos = i;
            }
        }
        rotate(points.begin(), points.begin() + pos, points.end());
        originPoints.push_back({0, 0});
        for (int i = 1; i < n; i++) {
            originPoints.push_back(points[i] - points[0]);
        }
    }

    int logpointOnPolygon(Point p) {
        /*
         * 0 -> on
         * 1 -> in
         * 2 -> out
         */
        if (originPoints.size() == 0) {
            fill();
        }
        p = p - points[0];
        /*
        for(int m = 1; m < (int)points.size() - 1; m++){
            Triangle t = {originPoints[0], originPoints[m + 1], originPoints[m]};
            Triangle t1 = {originPoints[m + 1], originPoints[m],p};
            if(t.onTriangle(p) && t1.signedArea() == 0){
                return 0;
            }
            if(t.inTriangle(p)){
                return 1;
            }
        }
         */
        //firstly, check if its inside the 0th triangle
        Triangle t0 = {originPoints[0], originPoints[1], originPoints[2]};
        Triangle t01 = {originPoints[1], p, originPoints[2]};
        if(t0.onTriangle(p) && t01.signedArea() == 0){
            //cout << "YES" << endl;
            return 0;
        }
        if(t0.inTriangle(p)){
            return 1;
        }
        Triangle tn = {originPoints[(int)points.size() - 1],originPoints[(int)points.size() - 2], originPoints[0]};
        Triangle tn1 = {originPoints[(int)points.size() - 1],originPoints[(int)points.size() - 2], p};
        if(tn.onTriangle(p) && tn1.signedArea() == 0){
            //cout << "YES" << endl;
            return 0;
        }
        if(tn.inTriangle(p)){
            //cout << "YES" << endl;
            return 1;
        }
        int l = 1;
        int r = (int)points.size() - 2;
        while (r - l > 1){
            int m = (l + r)/2;
            Triangle t = {originPoints[m], originPoints[m + 1],originPoints[0]};
            Triangle t1 = {originPoints[m], originPoints[m + 1],p};
            if(t.onTriangle(p) && t1.signedArea() == 0){
                return 0;
            }
            if(t.inTriangle(p)){
                return 1;
            }
            if(p.cross(originPoints[m]) > 0){
                r = m;
            }else{
                l = m;
            }
            //cout << l << " " << r << endl;
        }
        return 2;
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
    int q;
    cin >> q;
    while (q--) {
        Point p;
        cin >> p.x >> p.y;
        int x = polygon.logpointOnPolygon(p);
        if (x == 0) {
            cout << "BORDER \n";
        } else if (x == 1) {
            cout << "INSIDE \n";
        } else {
            cout << "OUTSIDE \n";
        }
    }
}

int main() {
    solve();
}
