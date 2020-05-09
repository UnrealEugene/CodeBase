#include <iostream>
#include <utility>
#include <numeric>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 1);
    for (int i = 0; i < n; i++)
        std::swap(p[i], p[i / 2]);
    for (int i = 0; i < n; i++)
        std::cout << p[i] << " ";
}
