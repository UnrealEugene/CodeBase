#include <iostream>
#include <numeric>
#include <string>
#include <vector>
 
int n, m, k;
std::string str[1050];
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    std::cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        std::cin >> str[i];
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    for (int i = 0; i < k; i++) {
        std::vector<std::vector<int>> v(26);
        for (int j = 0; j < n; j++)
            v[str[p[j]][m - i - 1] - 'a'].push_back(p[j]);
        int j = 0;
        for (int k = 0; k < 26; k++)
            for (int l : v[k]) p[j++] = l;
    }
    for (int i = 0; i < n; i++)
        std::cout << str[p[i]] << std::endl;
}
