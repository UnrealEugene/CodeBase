#include <bits/stdc++.h>

const int MOD = 1e9 + 7;
struct PolynomialBuilder {
	std::vector<std::vector<int>> p; 
	std::vector<int> inv;
	//Вычисление в конструкторе массивов разностей p
	PolynomialBuilder(const std::vector<int> &x) {
		p.push_back(x);
		while ((int)p.back().size() > 1) {
			std::vector<int> temp(p.back().size() - 1);
			for (int i = 0; i < (int)temp.size(); i++)
				temp[i] = (p.back()[i + 1] + MOD - p.back()[i]) % MOD;
			p.push_back(temp);
		}
		//Предпосчёт обратных элементов
		inv.resize(p.size() + 1);
		inv[1] = 1;
		for (int i = 2; i < (int)inv.size(); i++)
			inv[i] = (MOD - 1LL * (MOD / i) * inv[MOD % i] % MOD) % MOD;
	}
	//Вычисление значения в точке для значений |x| ~ 1e18
	int evaluate_at(long long x) { 
		x = (x % MOD + MOD) % MOD;
		int res = 0, binom = 1;
		for (int i = 0; i < (int)p.size(); i++) {
			//Если n < k и n >= 0, то Cnk(n, k) = 0
			if (x >= 0 && x < i)
				break;
			res = (res + 1LL * p[i][0] * binom % MOD + MOD) % MOD;
			binom = 1LL * binom * (x - i) % MOD * inv[i + 1] % MOD;
		}
		return res;
	}
};

int main() {
	PolynomialBuilder f({0, 1, 4}); 	//Задаем точками полином x^2
	std::cout << f.evaluate_at(3) << " "; 	//Вывод: 9
	std::cout << f.evaluate_at(-5); 	//Вывод: 25
}
