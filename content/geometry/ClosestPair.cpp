/**
 * Author: Simon Lindholm
 * Date: 2019-04-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/58747
 * Description: Finds the closest pair of points.
 * Time: O(n \log n)
 * Status: stress-tested
 */

// assumes points are long long, long double probably should work, but is slow
pair<vec, vec> closest(vector<vec> v) {
	assert(v.size() > 1);
	set<vec> S;
	sort(all(v), [](vec a, vec b) { return a.y < b.y; });
	pair<ll, pair<vec, vec>> ret{LLONG_MAX, {{0,0}, {0,0}}};
	int j = 0;
	for (vec p : v) {
		vec d{1 + (ll)sqrt(ret.first), 0};
		while (v[j].y <= p.y - d.x) S.erase(v[j++]);
		auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
		for (; lo != hi; ++lo)
			ret = min(ret, {len2(*lo - p), {*lo, p}});
		S.insert(p);
	}
	return ret.second;
}
