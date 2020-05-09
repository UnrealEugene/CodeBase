#include <iostream>
#include <utility>
#include <random>

int n, k, a, b, c;
int arr[30000050];
 
std::mt19937 rnd(time(0));

void kth_element(int l, int r, int cnt) {
    if (l + 1 >= r)
        return;
    int i = l, j = r - 1;
    int x = arr[l + rnd() % (r - l)];
    while (i < j) {
        while (arr[i] < x)
            i++;
        while (arr[j] > x)
            j--;
        if (i > j)
            break;
        std::swap(arr[i++], arr[j--]);
    }
    if (cnt <= j)
        kth_element(l, j + 1, cnt);
    else
        kth_element(j + 1, r, cnt);
}
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    std::cin >> n >> k >> a >> b >> c >> arr[0] >> arr[1];
    for (int i = 2; i < n; i++) {
        arr[i] = a * arr[i - 2] + b * arr[i - 1] + c;
    }
    kth_element(0, n, k - 1);
    std::cout << arr[k - 1] << std::endl;
    return 0;
}
