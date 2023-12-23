int gcd(int x, int y) {
  if(y == 0) return x;
  return gcd(y, x % y);
}

struct Point {
  int x, y;
  Point():x(0),y(0){}
  Point(int x, int y):x(x),y(y){}

  friend bool operator <(const Point& a, const Point& b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  }
};

using pt = Point;

struct Line {
  int a, b, c;
  Line(int a, int b, int c):a(a),b(b),c(c){}
  bool checkPoint(const pt& p) {
    return a * p.x + b * p.y + c == 0;
  }
};

Line make_line(pt p, pt q) {
  int A = p.y - q.y;
  int B = q.x - p.x;
  int C = -A * p.x - B * p.y;
  int gc = gcd(A, gcd(B, C));
  A /= gc; B /= gc; C /= gc;
  return Line(A, B, C);
}

double signed_atan2(double x, double y) {
  double val = atan2(x, y); // atan2l
  if(val < 0) val += 2 * PI;
  return val;
}

// clockwise
void sort_by_angle(vector<pt> &v, pt zero = {0, 0}) {
  sort(v.begin(), v.end(), [&] (pt a, pt b) {
    a.x -= zero.x; a.y -= zero.y;
    b.x -= zero.x; b.y -= zero.y;
    bool x = a < Point(), y = b < Point();
    return x == y ? a.x * b.y > a.y * b.x : x < y;
  });
}

// counterclockwise
void sort_by_angle2(vector<pt> &v, pt zero = {0, 0}) {
  stable_sort(v.begin(), v.end(), [&](auto a, auto b) {
    a.x -= zero.x; a.y -= zero.y;
    b.x -= zero.x; b.y -= zero.y;
    auto t1 = signed_atan2(a.x, a.y);
    auto t2 = signed_atan2(b.x, b.y);
    if(t1 == t2) return a < b;
      return t1 < t2;
    });
}
