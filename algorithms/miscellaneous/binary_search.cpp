#include <iostream>
#include <random>
 
std::mt19937 rnd(time(0));

int n, q, a[300500];
int lower_bound(int x) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) >> 1;
        if (a[m] >= x) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return r;
}
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::cin >> q;
    while (q--) {
        int x;
        std::cin >> x;
        if (a[lower_bound(x)] == x) {
            std::cout << lower_bound(x) + 1 << " " << lower_bound(x + 1) << std::endl;
        } else {
            std::cout << "-1 -1" << std::endl;
        }
    }
    return 0;
}
