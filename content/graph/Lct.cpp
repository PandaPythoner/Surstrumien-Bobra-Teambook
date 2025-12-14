/**
 * Author: Mangooste
 * Date: ?
 * Description: link-cut tree
 * Time: O(n\log(n))
 */

struct link_cut {
    struct node {
        int par;
        array<int, 2> sons;
        bool inv;
        int size;

        node() : par(-1), sons({ -1, -1 }), inv(false), size(1) {}
    };

    vector<node> t;

    int size() const {
        return t.size();
    }

    void push(int v) {
        if (t[v].inv) {
            t[v].inv = false;
            swap(t[v].sons[0], t[v].sons[1]);
            for (const auto u : t[v].sons)
                if (u != -1)
                    t[u].inv ^= 1;
        }
    }

    void relax(int v) {
        push(v);
        t[v].size = 1;
        for (const auto x : t[v].sons)
            if (x != -1)
                t[v].size += t[x].size;
    }

    void rotate(int v) {
        int u = t[v].par, w = t[u].par;
        push(u), push(v);
        t[v].par = w;
        if (w != -1)
            for (auto& x : t[w].sons)
                if (x == u)
                    x = v;
        int i = t[u].sons[1] == v;
        t[u].sons[i] = t[v].sons[i ^ 1];
        if (t[v].sons[i ^ 1] != -1)
            t[t[v].sons[i ^ 1]].par = u;
        t[v].sons[i ^ 1] = u;
        t[u].par = v;
        relax(u), relax(v);
    }

    bool is_root(int v) const {
        return t[v].par == -1 || (t[t[v].par].sons[0] != v && t[t[v].par].sons[1] != v);
    }

    void splay(int v) {
        while (!is_root(v)) {
            int u = t[v].par;
            if (!is_root(u))
                rotate((t[t[u].par].sons[0] == u) == (t[u].sons[0] == v) ? u : v);
            rotate(v);
        }
        push(v);
    }

    int expose(int v) {
        int prev = -1;
        for (int u = v; u != -1; prev = u, u = t[u].par) {
            splay(u);
            t[u].sons[1] = prev;
            relax(u);
        }
        splay(v);
        assert(t[v].sons[1] == -1 && t[v].par == -1);
        return prev;
    }

    link_cut(int n = 0) : t(n) {}

    int add() {
        t.push_back(node());
        return int(t.size()) - 1;
    }

    void set_root(int root) {
        expose(root);
        t[root].inv ^= 1;
        push(root);
    }

    bool connected(int v, int u) {
        if (v == u)
            return true;
        expose(v), expose(u);
        return t[v].par != -1;
    }

    bool link(int v, int u) {
        if (connected(v, u))
            return false;
        t[u].inv ^= 1;
        t[u].par = v;
        expose(u);
        return true;
    }

    bool cut(int v, int u) {
        if (v == u)
            return false;
        set_root(v), expose(u);
        if (t[u].sons[0] != v)
            return false;
        t[u].sons[0] = -1;
        relax(u);
        t[v].par = -1;
        return true;
    }

    int par(int v, int root) {
        if (!connected(v, root))
            return -1;
        set_root(root), expose(v);
        if (t[v].sons[0] == -1)
            return -1;
        v = t[v].sons[0];
        while (push(v), t[v].sons[1] != -1)
            v = t[v].sons[1];
        splay(v);
        return v;
    }

    int distance(int v, int u) {
        if (!connected(v, u))
            return -1;
        set_root(v), expose(u);
        return t[u].sons[0] == -1 ? 0 : t[t[u].sons[0]].size;
    }

    int lca(int v, int u, int root) {
        set_root(root), expose(v);
        return expose(u);
    }
};