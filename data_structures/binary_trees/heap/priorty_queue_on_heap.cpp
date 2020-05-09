#include <bits/stdc++.h>

 
class my_heap {
 private:
    std::vector<std::pair<int, int>> a;
    std::vector<int> pos;
 
    void _swap(int x, int y) {
        std::swap(pos[a[x].second], pos[a[y].second]);
        std::swap(a[x], a[y]);
    }
 
    int _sift_up(int i) {
        while (i > 0 && a[i].first < a[(i - 1) / 2].first) {
            _swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
        return i;
    }
 
    int _sift_down(int i) {
        while (2 * i + 1 < a.size()) {
            int j = 2 * i + 1;
            if (2 * i + 2 < a.size() && a[2 * i + 2].first < a[2 * i + 1].first)
                j = 2 * i + 2;
            if (a[i].first < a[j].first)
                break;
            _swap(i, j);
            i = j;
        }
        return i;
    }
 
 public:
    my_heap() { }
 
    void push(int val) {
        a.push_back({val, pos.size()});
        pos.push_back(a.size() - 1);
        _sift_up(a.size() - 1);
    }
 
    std::pair<int, int> extract_min() {
        if (a.empty())
            return {-1, -1};
        _swap(0, a.size() - 1);
        std::pair<int, int> res = a.back();
        a.pop_back();
        pos[res.second] = -1;
        _sift_down(0);
        return res;
    }
 
    void decrease_key(int q, int val) {
        if (pos[q] == -1)
            return;
        a[pos[q]].first = val;
        _sift_up(pos[q]);
    }
};
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0); 
    my_heap h;
    std::string t;
    int j = 0;
    std::vector<int> to, from;
    while (std::cin >> t) {
        to.push_back(-1);
        if (t == "push") {
            int a;
            std::cin >> a;
            h.push(a);
            from.push_back(to.size() - 1);
            to.back() = j++;
        } else if (t == "extract-min") {
            std::pair<int, int> ans = h.extract_min();
            if (ans.second == -1) {
                std::cout << "*" << std::endl;
            } else {
                std::cout << ans.first << " " << from[ans.second] + 1 << std::endl;
                assert(from[ans.second] != -1);
            }
        } else if (t == "decrease-key") {
            int a, b;
            std::cin >> a >> b;
            h.decrease_key(to[a - 1], b);
        }
    }
}
