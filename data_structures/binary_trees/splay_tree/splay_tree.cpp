#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <deque>
#include <queue>
#include <stack>
#include <vector>
#include <tuple>
#include <random>
#include <time.h>
#include <math.h>
#include <fstream>
#include <memory.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
typedef __gnu_pbds::tree<long long, __gnu_pbds::null_type, less<long long>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ordered_set;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const long long BASE = 10000, INF = 2147483647, MOD = 1000000007;
const long long LL_INF = 9223372036854775807LL;
const double PI = 3.141592653589793238;
const long long MAX_N = 1000000000;

template<typename T> class splay {
private:
    size_t t_size = 0;
    struct node {
        node* left, *right;
        node* parent;
        T value;
        unsigned int c;
        node(const T& value = T())
        :left(nullptr), right(nullptr), parent(nullptr), value(value) { }
        ~node() { }
    } *root = nullptr;
    void _rotate(node *x) {
        node *y = x->parent, *g = y->parent;
        if (x == y->left) {
            if (g) {
                if (y == g->left) g->left = x;
                else if (y == g->right) g->right = x;
            }
            node *b = x->right;
            x->parent = g;
            x->right = y;
            y->parent = x;
            y->left = b;
            if (b) b->parent = y;
        }
        else if (x == y->right) {
            if (g) {
                if (y == g->left) g->left = x;
                else if (y == g->right) g->right = x;
            }
            node *b = x->left;
            x->parent = g;
            x->left = y;
            y->parent = x;
            y->right = b;
            if (b) b->parent = y;
        }
        if (root == y) root = x;
    }
    void _zig(node* x) {
        _rotate(x);
    }
    void _zigzig(node* x) {
        _rotate(x->parent);
        _rotate(x);
    }
    void _zigzag(node* x) {
        _rotate(x);
        _rotate(x);
    }
    void _splay(node* x) {
        while (x != root) {
            if (x->parent == root)
                _zig(x);
            else {
                node *p = x->parent, *g = p->parent;
                if ((x == p->left && p == g->left) || (x == p->right && p == g->right))
                    _zigzig(x);
                else if ((x == p->left && p == g->right) || (x == p->right && p == g->left))
                    _zigzag(x);
            }
        }
    }
    node* _find_min(node* x) {
        while (x && x->left)
            x = x->left;
        return x;
    }
    node* _find_max(node* x) {
        while (x && x->right)
            x = x->right;
        return x;
    }
    void _replace(node *x, node *y) {
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) y->parent = x->parent;
    }
    node* _find(const T& v) {
        node* x = root;
        while (x && x->value != v) {
            if (x->value < v) {
                if (x->right) x = x->right;
                else return x;
            }
            else if (v < x->value) {
                if (x->left) x = x->left;
                else return x;
            }
        }
        if (x) _splay(x);
        return x;
    }
    node* _successor(node* x) {
        if (x->right) return _find_min(x->right);
        while (x->parent && x == x->parent->right)
            x = x->parent;
        return x->parent;
    }
    node* _predecessor(node* x) {
        if (x->left) return _find_max(x->left);
        while (x->parent && x == x->parent->left) x = x->parent;
        return x->parent;
    }
public:
    bool find(const T& v) {
        node *x = _find(v);
        if (!x) return false;
        return x->value == v;
    }
    void insert(const T& v) {
        if (t_size == 0) {
            root = new node(v);
            t_size++;
        }
        else {
            node* x = _find(v);
            if (x->value == v) {
                _splay(x);
                return;
            }
            t_size++;
            node *z = new node(v);
            z->parent = x;
            if (v < x->value) x->left = z;
            else if (x->value < v) x->right = z;
            _splay(z);
        }
    }
    void erase(const T& v) {
        node* x = _find(v);
        if (!x || x->value != v) return;
        _splay(x);
        if (!x->left) _replace(x, x->right);
        else if (!x->right) _replace(x, x->left);
        else {
            node* y = _find_min(x->right);
            if (y->parent != x) {
                _replace(y, y->right);
                y->right = x->right;
                y->right->parent = y;
            }
            _replace(x, y);
            y->left = x->left;
            y->left->parent = y;
        }
        delete x;
        t_size--;
    }
    void print() {
        cout << "[";
        int i = 0;
        for (node *x = _find_min(root); x; x = _successor(x), i++) {
            if (i) cout << ", ";
            cout << x->value;
        }
        cout << "]";
    }
    size_t size() { return t_size; }
    bool empty() { return !t_size; }
};
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    splay<int> tr;
    for (int i = 0; i < n; i++) {
        int a;
        string s;
        cin >> s;
        if (s == "add") {
            cin >> a;
            size_t sz = tr.size();
            tr.insert(a);
            if (tr.size() - sz == 1) cout << "true\n";
            else cout << "false\n";
        }
        else if (s == "delete") {
            cin >> a;
            size_t sz = tr.size();
            tr.erase(a);
            if (sz - tr.size() == 1) cout << "true\n";
            else cout << "false\n";
        }
        else if (s == "find") {
            cin >> a;
            if (tr.find(a)) cout << "true\n";
            else cout << "false\n";
        }
    }
    return 0;
}
