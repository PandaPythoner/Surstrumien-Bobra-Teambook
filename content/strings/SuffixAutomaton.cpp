/**
 * Author: Anton Stepanov
 * Date: 2025-10-27
 * Description: Build suffix automaton.
 * Time: O(n)
 */
const int alpha = 26;

struct state {
    int len, link;
    array<int, alpha> next;
};
state st[MAXLEN * 2];
int sz, last;

void sa_init() {
    sz = last = 0;
    st[0].len = 0;
    st[0].link = -1;
    st[0].next.fill(-1);
    ++sz;
}

int sa_cut(int v, int c) {
    assert(st[v].next[c] != -1);
    int to = st[v].next[c];
    if (st[to].len == st[v].len + 1) {
        return to;
    }
    int clone = sz++;
    st[clone].len = st[v].len + 1;
    st[clone].next = st[to].next;
    st[clone].link = st[to].link;
    for (; v != -1 && st[v].next[c] == to; v = st[v].link)
        st[v].next[c] = clone;
    st[to].link = clone;
    return clone;
}

void sa_extend(int c) {
    if (st[last].next[c] != -1) {
        int to = sa_cut(last, c);
        last = to;
        return;
    }
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].next.fill(-1);
    int v;
    for (v = last; v != -1 && st[v].next[c] == -1; v = st[v].link)
        st[v].next[c] = cur;
    if (v == -1)
        st[cur].link = 0;
    else {
        int to = st[v].next[c];
        st[cur].link = sa_cut(v, c);
    }
    last = cur;
}