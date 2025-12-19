/**
 * Author: Anton Stepanov
 * Date: 2025-12-19
 * Description: Solving linear systems modulo 2 (returns solution and rank)
 * Time: O(n^3/w)
 */

using bt = bitset<maxn>;
pair<bt, int> gauss_binary(vector<bt> a, int n, int m) {
    int row = 0;
    for (int col = 0; col < m and row < n; col += 1) {
        for (int i = row; i < n; i += 1) {
            if (a[i][col] != 0) {
                swap(a[row], a[i]);
                break;
            }
        }
        if (a[row][col] == 0)
            continue;
        for (int i = row + 1; i < n; i += 1) {
            if (a[i][col] == 0) {
                continue;
            }
            a[i] ^= a[row];
        }
        ++row;
    }
    for (int i = row; i < n; i += 1) {
        if (a[i][m] != 0) {
            return { bt(), -1 };
        }
    }
    bt cur;
    cur.reset();
    for (int i = row - 1; i >= 0; i -= 1) {
        int value = (cur & a[i]).count() % 2;
        if (value != a[i][m]) {
            int pos = a[i]._Find_first();
            assert(pos < m);
            cur.set(pos);
        }
    }
    return { cur, row };
}