#include <iostream>
#include <utility>
#include <random>
#include <algorithm>
 
std::mt19937 rnd(time(0));

int n, a[300500];

void quicksort(int *a, int l, int r) {
    if (l + 1 >= r)
        return;
    int x = a[(l + r) >> 1];
    int i = l, j = r - 1;
    while (i <= j) {
        while (a[i] < x)
            i++;
        while (a[j] > x)
            j--;
        if (i > j)
            break;
        std::swap(a[i++], a[j--]);
    }
    quicksort(a, l, j + 1);
    quicksort(a, j + 1, r);
}
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::shuffle(a, a + n, rnd);
    quicksort(a, 0, n);
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    return 0;
}
