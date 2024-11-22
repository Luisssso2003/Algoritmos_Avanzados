#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

struct Point {
    int x, y, index;
};

double distance(const Point &a, const Point &b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

int cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

std::vector<Point> convexHull(std::vector<Point> &points) {
    std::sort(points.begin(), points.end(), [](const Point &p1, const Point &p2) {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    });

    std::vector<Point> hull;

    for (const auto &p : points) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    size_t lower_size = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        while (hull.size() > lower_size && cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    hull.pop_back();
    return hull;
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        if (n == 1) {
            int x, y;
            std::cin >> x >> y;
            std::cout << "0.00\n1\n\n";
            continue;
        }

        std::vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> points[i].x >> points[i].y;
            points[i].index = i + 1;
        }

        std::vector<Point> hull = convexHull(points);

        double perimeter = 0.0;
        for (size_t i = 0; i < hull.size(); ++i) {
            perimeter += distance(hull[i], hull[(i + 1) % hull.size()]);
        }

        std::cout << std::fixed << std::setprecision(2) << perimeter << "\n";
        for (const auto &p : hull) {
            std::cout << p.index << " ";
        }
        std::cout << "\n\n";
    }

    return 0;
}
