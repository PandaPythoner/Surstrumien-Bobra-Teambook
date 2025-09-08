/**
 * Author: Anton Stepanov
 * Date: 2025-08-09
 * Description: Find number of right-up paths from (0, 0) to (x, y), not
 * touching lines y=x+l and y=x+r Time: O((x + y)/(r - l))
 */

mint flex(ll x, ll y, ll l, ll r) {
  if (l >= 0 or r <= 0) {
    return 0;
  }
  ll n = x + y;
  mint res = 0;
  for (ll k = -(n / (r - l)); k <= n / (r - l); k += 1) {
    res += cnk(n, x + k * (r - l));
    res -= cnk(n, y - r + k * (r - l));
  }
  return res;
}