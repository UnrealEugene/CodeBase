#include <iostream>
#include <vector>
 
bool is_heap(const std::vector<int> &a) {
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] < a[(i - 1) >> 1])
            return false;
    }
    return true;
}
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &x : a)
        std::cin >> x;
    std::cout << (is_heap(a) ? "YES" : "NO");
}
