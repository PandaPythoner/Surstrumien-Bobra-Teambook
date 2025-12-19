/**
 * Author: Anton Stepanov
 * Date: 2025-12-19
 * Description: Checking primality of p
 * Time: O(\log(C))
 */
ll binpow(ll x, ll n, ll mod) {
    ll res = 1;
    for (ll i = 1; i <= n; i *= 2, x = (__int128_t)x * x % mod) {
        if (n & i) {
            res = (__int128_t)res * x % mod;
        }
    }
    return res;
}

bool isprime(ll p) {
    if (p == 1 || p == 4)
        return 0;
    if (p == 2 || p == 3)
        return 1;
    // for(ll a: {2, 7, 61}){
    // for(ll a: {2, 325, 9375, 28178, 450775, 9780504, 1795265022}){
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a % p == 0)
            continue;
        ll nw = p - 1;
        while (nw % 2 == 0)
            nw /= 2;
        ll x = binpow(a, nw, p); // int128
        if (x == 1)
            continue;
        ll last = x;
        nw *= 2;
        while (nw <= p - 1) {
            x = (__int128_t)x * x % p;
            if (x == 1) {
                if (last != p - 1) {
                    return 0;
                }
                break;
            }
            last = x;
            nw *= 2;
        }
        if (x != 1)
            return 0;
    }
    return 1;
}