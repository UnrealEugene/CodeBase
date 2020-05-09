#include <iostream>
#include <utility>
#include <numeric>
 
int n, a[100500], ans[100500];
void anti_qsort(int l, int r) {
    if (l == r)
        return;
    std::swap(a[(l + r) >> 1], a[r]);
    anti_qsort(l, r - 1);
}
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    std::cin >> n;
    std::iota(a, a + n, 0);
    anti_qsort(0, n - 1);
    for (int i = 0; i < n; i++)
        ans[a[i]] = i;
    for (int i = 0; i < n; i++)
        std::cout << ans[i] + 1 << " ";
}
