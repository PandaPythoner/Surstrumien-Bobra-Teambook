/**
 * Author: Alexey Mikhnenko
 * Date: ???
 * Description: Palindrome Tree
 * Time: O(n)
 */
struct palindromic_tree {
    int new_node() {
        tree.push_back(node());
        return static_cast<int>(tree.size()) - 1;
    }

    int find_suffix(int v) {
        int n = str.size();
        while (tree[v].length == n - 1 || str.back() != str[n - 2 - tree[v].length]) {
            v = tree[v].suflink;
        }
        return v;
    }

    struct node {
        int length = 0, suflink = -1, to[ALPHABET];
        node() { memset(to, -1, sizeof(to)); }
    };

    int even, odd, last;
    vector<node> tree;
    vector<int> str;

    palindromic_tree() {
        odd = new_node();
        even = new_node();
        tree[even].suflink = tree[odd].suflink = odd;
        tree[odd].length = -1;
        last = even;
    }

    void add(int symbol) {
        str.push_back(symbol);
        last = find_suffix(last);
        if (tree[last].to[symbol] == -1) {
            int v = new_node();
            tree[v].length = tree[last].length + 2;
            int u = find_suffix(tree[last].suflink);
            if (tree[u].to[symbol] != -1) {
                tree[v].suflink = tree[u].to[symbol];
            }
            else {
                tree[v].suflink = even;
            }
            tree[last].to[symbol] = v;
        }
        last = tree[last].to[symbol];
    }
};
