/**
 * Author: Anton Stepanov
 * Date: 2025-07-27
 * Description: Fast FFT!
 * Time: O(n\log(n))
 */
// Don't use Ofast, potential slow down by 2x!
// Write mint first!

int maxn, maxk;
vector<int> rvi;
vector<mint> wpws;

void build_fft(int _maxk) {
  maxk = _maxk;
  maxn = (1 << maxk);
  rvi.resize(maxn);
  rvi[0] = 0;
  for (int i = 1; i < maxn; i += 1) {
    rvi[i] = (rvi[i >> 1] >> 1);
    if (i & 1) {
      rvi[i] |= (1 << (maxk - 1));
    }
  }
  mint w = mint(3).pow((mod - 1) / maxn);
  mint pw = 1;
  wpws.resize(maxn);
  rep(i, maxn) {
    wpws[rvi[i]] = pw;
    pw *= w;
  }
}

void fft(vector<mint> &a, int k) {
  int n = (1 << k);
  for (int ln = n / 2; ln >= 1; ln /= 2) {
    int ln2 = ln * 2;
    for (int i = 0; i < n; i += ln2) {
      auto w = wpws[i / ln];
      for (int j = i; j < i + ln; j += 1) {
        auto u = a[j];
        auto v = a[j + ln] * w;
        a[j] = u + v;
        a[j + ln] = u - v;
      }
    }
  }
  rep(i, n) {
    int mrv = (rvi[i] >> (maxk - k));
    if (mrv < i) {
      swap(a[i], a[mrv]);
    }
  }
}

void inv_fft(vector<mint> &a, int k) {
  fft(a, k);
  int n = (1 << k);
  mint invn = mint(n).inv();
  rep(i, n) {
    a[i] *= invn;
  }
  reverse(a.begin() + 1, a.end());
}

vector<mint> mul(vector<mint> a, vector<mint> b) {
  if (a.empty() or b.empty()) {
    return {};
  }
  auto ca = a;
  auto cb = b;
  int lna = len(a);
  int lnb = len(b);
  int k = __lg(lna + lnb - 1);
  if (lna + lnb - 1 == (1 << k) + 1) {
    auto c = mul(vector<mint>(a.begin(), a.end() - 1), b);
    c.resize(lna + lnb - 1);
    rep(j, lnb) {
      c[lna - 1 + j] += a[lna - 1] * b[j];
    }
    return c;
  }
  if (lna + lnb - 1 > (1 << k)) {
    k += 1;
  }
  int n = (1 << k);
  a.resize(n);
  b.resize(n);
  fft(a, k);
  fft(b, k);
  rep(i, n) {
    a[i] *= b[i];
  }
  inv_fft(a, k);
  a.resize(lna + lnb - 1);
  return a;
}

vector<mint> operator+(vector<mint> a, vector<mint> b) {
  a.resize(max(a.size(), b.size()));
  for (int i = 0; i < (int)b.size(); ++i) {
    a[i] += b[i];
  }
  return a;
}

vector<mint> operator-(vector<mint> a, vector<mint> b) {
  a.resize(max(a.size(), b.size()));
  for (int i = 0; i < (int)b.size(); ++i) {
    a[i] -= b[i];
  }
  return a;
}

vector<mint> inv(const vector<mint> &a, int need) {
  vector<mint> b = {a[0].inv()};
  while ((int)b.size() < need) {
    vector<mint> a1 = a;
    int m = b.size();
    a1.resize(min((int)a1.size(), 2 * m));
    b = mul(b, vector<mint>{2} - mul(a1, b));
    b.resize(2 * m);
  }
  b.resize(need);
  return b;
}

vector<mint> mul2(vector<mint> a, vector<mint> b) {
  int lna = len(a);
  int lnb = len(b);
  int k = 0;
  while ((1 << k) < lna) {
    ++k;
  }
  int n = (1 << k);
  a.resize(n);
  reverse(all(b));
  b.resize(n);
  fft(a, k);
  fft(b, k);
  rep(i, n) {
    a[i] *= b[i];
  }
  inv_fft(a, k);
  vector<mint> c(lna - lnb + 1);
  rep(i, len(c)) {
    c[i] = a[lnb - 1 + i];
  }
  return c;
}

vector<mint> multipoint(vector<mint> a, vector<mint> x) {
  int n = x.size();
  int m = len(a);
  vector<vector<mint>> tree(2 * n);
  for (int i = 0; i < n; ++i) {
    tree[i + n] = {1, 0 - x[i]};
  }
  for (int i = n - 1; i; --i) {
    tree[i] = mul(tree[2 * i], tree[2 * i + 1]);
  }
  auto tinv = inv(tree[1], m);
  a.resize(n + m - 1);
  auto c = mul2(a, tinv);
  tree[1] = c;
  for (int i = 1; i < n; i += 1) {
    auto x = tree[i + i];
    auto y = tree[i + i + 1];
    tree[i + i] = mul2(tree[i], y);
    tree[i + i + 1] = mul2(tree[i], x);
  }
  vector<mint> res(n);
  for (int i = 0; i < n; ++i) {
    res[i] = tree[i + n][0];
  }
  return res;
}

vector<mint> div(vector<mint> a, vector<mint> b) {
  int n = a.size() - 1;
  int m = b.size() - 1;
  if (n < m) {
    return {0};
  }
  reverse(all(a));
  reverse(all(b));
  a.resize(n - m + 1);
  b.resize(n - m + 1);
  vector<mint> c = inv(b, b.size());
  vector<mint> q = mul(a, c);
  q.resize(n - m + 1);
  reverse(all(q));
  return q;
}

vector<mint> mod_poly(vector<mint> a, vector<mint> b) {
  auto res = a - mul(b, div(a, b));
  res.resize(len(b) - 1);
  return res;
}

vector<mint> deriv(vector<mint> a) {
  for (int i = 1; i < (int)a.size(); ++i) {
    a[i - 1] = a[i] * i;
  }
  a.back() = 0;
  if (a.size() > 1) {
    a.pop_back();
  }
  return a;
}

vector<mint> integ(vector<mint> a) {
  a.push_back(0);
  for (int i = (int)a.size() - 1; i; --i) {
    a[i] = a[i - 1] * mint(i).inv();
  }
  a[0] = 0;
  return a;
}

vector<mint> log(vector<mint> a, int n) {
  auto res = integ(mul(deriv(a), inv(a, n)));
  res.resize(n);
  return res;
}

vector<mint> exp(vector<mint> a, int need) {
  vector<mint> b = {1};
  while ((int)b.size() < need) {
    vector<mint> a1 = a;
    int m = b.size();
    a1.resize(min((int)a1.size(), 2 * m));
    a1[0] += 1;
    b = mul(b, a1 - log(b, 2 * m));
    b.resize(2 * m);
  }
  b.resize(need);
  return b;
}