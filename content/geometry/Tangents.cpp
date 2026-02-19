/**
 * Author: Igor Markelov
 * Date: 2022-11-18
 * Description: Tangents to circles.
 */
// tangents from vec to circle
int tangents(vec &o, ld r, vec &p, vec &i1, vec &i2) {
    ld ln = len(o - p);
    int sgn = sign(ln - r);
    if (sgn == -1) {
        return 0;
    } else if (sgn == 0) {
        i1 = p;
        return 1;
    } else {
        ld x = sq(r) / ln;
        vec v = norm(p - o) * x;
        vec a = o + v;
        v = ort(norm(p - o)) * sqrt(sq(r) - sq(x));
        i1 = a + v;
        i2 = a - v;
        return 2;
    }
}

void _tangents(vec c, ld r1, ld r2, vector<line> &ans) {
    ld r = r2 - r1;
    ld z = sq(c.x) + sq(c.y);
    ld d = z - sq(r);
    if (sign(d) == -1)
        return;
    d = sqrt(abs(d));
    line l;
    l.a = (c.x * r + c.y * d) / z;
    l.b = (c.y * r - c.x * d) / z;
    l.c = r1;
    ans.push_back(l);
}
// tangents between two circles
vector<line> tangents(vec o1, ld r1, vec o2, ld r2) {
    vector<line> ans;
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2)
            _tangents(o2 - o1, r1 * i, r2 * j, ans);
    for (int i = 0; i < (int)ans.size(); ++i)
        ans[i].c -= ans[i].a * o1.x + ans[i].b * o1.y;
    return ans;
}
