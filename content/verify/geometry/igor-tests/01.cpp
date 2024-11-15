// Yandex Algo 2023-2024. C. Геометрия 1 A - Площадь треугольника
// https://ejudge.algocode.ru/cgi-bin/new-client?contest_id=55061
#define main main228
#include "../../../contest/template.cpp"
#undef main

#include "../../../geometry/Point.cpp"

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(20), cout.setf(ios::fixed);
    point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    cout << abs((b - a) % (c - a)) / 2 << endl;
}
