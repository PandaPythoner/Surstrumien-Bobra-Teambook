/**
 * Author: Alexey Mikhnenko
 * Date: Unknown
 * Description: finds $\sum_{x = 0}^{n - 1} \lfloor(kx + b) / m\rfloor$.
 * Reqire $k \geq 0, b \geq 0, m \ge 0, n \geq 0$.
 */

template<typename T>
T floor_sum(T k, T b, T m, T n) {
    if (k == 0) {
        return (b / m) * n;
    }
    if (k >= m || b >= m) {
        return n * (n - 1) / 2 * (k / m) + n * (b / m) + floor_sum(k % m, b % m, m, n);
    }
    T ymax = (k * (n - 1) + b) / m;
    return n * ymax - floor_sum(m, m + k - b - 1, k, ymax);
}