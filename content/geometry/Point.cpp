/**
 * Author: alexxela12345,daubi,talant
 * Date: 2024-08-03
 * Description: struct vec
 */

const ld EPS = 1e-7;

ld sq(ld x) {
    return x * x;
}

int sign(ld x) {
    if (x < -EPS) {
        return -1;
    }
    if (x > EPS) {
        return 1;
    }
    return 0;
}

struct vec {//% - cross, * - dot
    ld x, y;
    auto operator<=>(const vec&) const = default;
};
ld operator*(const vec &a, const vec &b) {
    return a.x * b.x + a.y * b.y;
}
ld operator%(const vec &a, const vec &b) {
    return a.x * b.y - a.y * b.x;
}
vec operator-(const vec &a, const vec &b) {
    return {a.x - b.x, a.y - b.y};
}
vec operator+(const vec &a, const vec &b) {
    return {a.x + b.x, a.y + b.y};
}
vec operator*(const vec &a, ld b) {
    return {a.x * b, a.y * b};
}
vec operator/(const vec &a, ld b) {
    return {a.x / b, a.y / b};
}
bool operator<(const vec &a, const vec &b)  {
    if (sign(a.y - b.y) != 0) {
        return a.y < b.y;
    } else if (sign(a.x - b.x) != 0) {
        return a.x < b.x;
    }
    return 0;
}
ld len2(const vec &a) {
    return sq(a.x) + sq(a.y);
}
ld len(const vec &a) {
    return sqrt(len2(a));
}
vec norm(vec a) {
    return a / len(a);
}
int half(vec a) {
    return (sign(a.y) == -1 || (sign(a.y) ==0 && a.x < 0));
}
vec ort(vec a) {
    return {-a.y, a.x};
}
vec turn(vec a, ld ang) {
    return {a.x * cos(ang) - a.y * sin(ang), a.x * sin(ang) + a.y * cos(ang)};
}
ld getAngle(vec &a, vec &b) {
    return atan2(a % b, a * b);
}
bool cmpHalf(const vec &a, const vec &b) {
    if (half(a) != half(b)) {
        return half(b);
    } else {
        int sgn = sign(a % b);
        if (!sgn) {
            return len2(a) < len2(b);
        } else {
            return sgn == 1;
        }
    }
}
