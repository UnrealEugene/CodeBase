#include <bits/stdc++.h>
 
const int INF = 1000000;
 
template<typename T, typename Cmp = std::less<T>>
class DSU {
 private:
    int sz = -1;
    std::vector<int> p, r;
    std::vector<T> val, mx, mn;
 
 public:
    DSU(const int &_size, const std::vector<T> &v) {
        assert(_size > 0);
        p.resize(_size);
        std::iota(p.begin(), p.end(), 0);
        r.assign(_size, 1);
        val = mx = mn = v;
        sz = _size;
    }
 
    DSU(const int &_size) : DSU(_size, std::vector<T>(_size)) { }
 
    int get(int x) {
        assert(x >= 0 && x < sz);
        if (p[x] != x)
            p[x] = get(p[x]);
        return p[x];
    }
 
    int get_size(int x) {
        assert(x >= 0 && x < sz);
        return r[get(x)];
    }
 
    T get_val(int x) {
        assert(x >= 0 && x < sz);
        return val[x];
    }
 
    T get_min(int x) {
        assert(x >= 0 && x < sz);
        return mn[get(x)];
    }
 
    T get_max(int x) {
        assert(x >= 0 && x < sz);
        return mx[get(x)];
    }
 
    int size() {
        return sz;
    }
 
    void set_val(int x, T v) {
        assert(x >= 0 && x < sz);
        val[x] = v;
        int pp = get(x);
        mn[pp] = Cmp()(val[x], mn[pp]) ? val[x] : mn[pp];
        mx[x] = Cmp()(val[x], mx[pp]) ? mx[pp] : val[x];
    }
 
    bool unite(int x, int y) {
        x = get(x); y = get(y);
        if (x == y)
            return false;
        if (r[x] < r[y])
            std::swap(x, y);
        p[y] = x;
        r[x] += r[y];
        mn[x] = Cmp()(mn[x], mn[y]) ? mn[x] : mn[y];
        mx[x] = Cmp()(mx[x], mx[y]) ? mx[y] : mx[x];
        return true;
    }
};
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int n;
    std::cin >> n;
    std::string str;
    std::vector<int> vals(n);
    std::iota(vals.begin(), vals.end(), 1);
    DSU<int> dsu(n, vals);
    while (std::cin >> str) {
        if (str == "get") {
            int x;
            std::cin >> x;
            std::cout << dsu.get_min(x - 1) << " " << dsu.get_max(x - 1) << " " << dsu.get_size(x - 1) << std::endl;
        } else {  // "unite"
            int x, y;
            std::cin >> x >> y;
            dsu.unite(x - 1, y - 1);
        }
    }
}
