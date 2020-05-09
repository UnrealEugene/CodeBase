#include <bits/stdc++.h>

using namespace std;
const long double maxArg = 1e14, EPS = 1e-9;
long double value(vector<double> &koef, double x) {
    long double ans = 0;
    for (int i = 0; i < koef.size(); i++) {
        long double k = koef[i];
        for (int j = 0; j < i; j++) k *= x;
        ans += k;
    }
    return ans;
}
bool findZero(vector<double> &koef, double l, double r, bool up, double &zero){
    double vl = value(koef, l), vr = value(koef, r);
    if ((vl > 0 && vr > 0) || (vl < 0 && vr < 0)) return false;
    while (r - l > EPS) {
        double x = (r + l) / 2;
        if (value(koef, x) > 0) {
            if (up) r = x;
            else l = x;
        } else {
            if (up) l = x;
            else r = x;
        }
    }
    zero = l;

    return true;
}
void devariative(vector<double> koef, vector<double> &zeros) {
    if (koef.size() == 2)
        zeros.push_back(-koef[0]/koef[1]);
    else {
        vector<double> newKoef;
        for (int i = 1; i < (int)koef.size(); i++)
            newKoef.push_back(koef[i]*i);
        devariative(newKoef, zeros);
        vector<double> newZeros;
        for (int i = 0; i <= zeros.size(); i++) {
            bool up = false;
            double l, r, zero = 0;
            if (i == 0)
                l = -maxArg;
            else if (i > 0)
                l = zeros[i - 1];
            if (i == zeros.size())
                r = maxArg;
            else if (i < zeros.size())
                r = zeros[i];
            if (i < zeros.size()) {
                if (value(koef, (l+r)/2) < value(koef, zeros[i]))
                    up = true;
            }
            else {
                if (value(koef, (l+r)/2) > value(koef, zeros[i]))
                    up = true;
            }
            if (findZero(koef, l, r, up, zero))
                newZeros.push_back(zero);
        }
        zeros.clear();
        zeros = newZeros;
    }
}
int main()
{
    //cout << setprecision(5);
    vector<double> koef;
    double k;
    int n;
    cin >> n;
    for (int i = 0; i <=     n; i++) {
        cin >> k;
        koef.push_back(k);
    }
    reverse(koef.begin(), koef.end());
    vector<double> zeros;
    devariative(koef, zeros);
    cout.precision(6);
    if (!zeros.size())
        cout << "NO SOLUTIONS";
    else {
        for (int i = 0; i < (int)zeros.size(); i++) {
            if (!i || abs(zeros[i] - zeros[i-1]) > 300*EPS)
                cout << fixed << zeros[i] << endl;
        }
    }
    return 0;
}
