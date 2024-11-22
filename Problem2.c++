#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Point {
    int x, y, index;
    bool operator<(const Point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

double distance(const Point &a, const Point &b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point> convexHull(vector<Point> &points) {
    sort(points.begin(), points.end());
    vector<Point> hull;

    for (const auto &p : points) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    size_t lower_size = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        while (hull.size() > lower_size && cross(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    hull.pop_back();
    return hull;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        if (n == 1) {
            int x, y;
            cin >> x >> y;
            cout << "0.00\n1\n\n";
            continue;
        }

        vector<Point> points;
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            points.push_back({x, y, i + 1});
        }

        vector<Point> hull = convexHull(points);

        double perimeter = 0.0;
        for (size_t i = 0; i < hull.size(); ++i) {
            perimeter += distance(hull[i], hull[(i + 1) % hull.size()]);
        }

        cout << fixed << setprecision(2) << perimeter << "\n";
        for (const auto &p : hull) {
            cout << p.index << " ";
        }
        cout << "\n\n";
    }
    return 0;
}
