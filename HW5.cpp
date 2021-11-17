#include <iostream>
#include <valarray>
#include <vector>

using namespace std;

valarray <double> Gaus(vector <valarray<double>> a) {
    unsigned n = a.size();
    valarray <double> ans(n);
    double coef;
    for (unsigned i = 0; i < n; ++i) {
        unsigned j;
        for (j = i; j < n && a[j][i] == 0; ++j);
        if (j == n) {
            cout << "System has no solution or their quantity is infinity" << endl;
            exit(0);
        }
        if (i != j)
            swap(a[j], a[i]);
        for (j = 0; j < n; ++j) {
            if (j == i) continue;
            coef = a[j][i] / a[i][i];
            a[j] -= a[i] * coef;
        }
    }
    for (unsigned i = 0; i < n; ++i)
        ans[i] = a[i][n] / a[i][i];
    return ans;
}

void SquareAproximation(valarray<double>* data) {
	unsigned size = data[0].size();
	vector<valarray<double>> suem(3);
	valarray<double> abc;
	vector<double> koef(7, 0);
	for (unsigned i = 0; i < 7; ++i) {
		if (i < 4) {
			for (unsigned j = 0; j < size; ++j) {
				koef[i] += pow(data[0][j], i + 1);//иксы
			}
		}
		else {
			for (unsigned j = 0; j < size; ++j) {
				koef[i] += data[1][j] * pow(data[0][j], i - 4);//игреки
			}
		}
	}
	for (unsigned i = 0; i < 3; ++i) {
		suem[i].resize(4);
		for (unsigned j = 0; j < 3; ++j) {
			if (i != 2 || j != 2) {
				suem[i][j] = koef[3 - j - i];
			}
			else {
				suem[i][j] = size;
			}
		}
		suem[i][3] = koef[6 - i];
	}
	abc = Gaus(suem);
    cout << "SqrAp(x) = " << abc[0] << "x^2 + " << abc[1] << "x + " << abc[2] << endl;
	double Discrepancy = 0;
	for (int i = 0; i < size; i++) {
		Discrepancy += pow(abc[0] * data[0][i] * data[0][i] + abc[1]*data[0][i] + abc[2] - data[1][i], 2);
	}
    cout << "Discrepancy = " << Discrepancy << endl;
}

void LinearApproximation(valarray<double>* data)
{
	unsigned size = data[0].size();
	vector<double> koef(4, 0);
	valarray<double> ans;
	for (int i = 0; i < size; i++) {
		koef[0] += data[0][i];
		koef[1] += pow(data[0][i], 2);
		koef[2] += data[1][i];
		koef[3] += data[0][i] * data[1][i];
	}
	vector<valarray<double>> syst(2);
	for (auto& el : syst) el.resize(3);
	syst[0][0] = koef[1];
	syst[0][1] = koef[0];
	syst[0][2] = koef[3];
	syst[1][0] = koef[0];
	syst[1][1] = size;
	syst[1][2] = koef[2];
	ans = Gaus(syst);
    cout << "LinAp(x) = " << ans[0] << "x + " << ans[1] << endl;
	double Discrepancy = 0;
	for (int i = 0; i < size; i++) {
		Discrepancy += pow(ans[0] * data[0][i] + ans[1] - data[1][i], 2);
	}
    cout << "Discrepancy = " << Discrepancy << endl;
}

int main(){
    valarray<double> data[2];
    double x_o = 2, y_o;
	unsigned n;
    cout << "Enter number of points:" << endl;
    cin >> n;
    data[0].resize(n);
    data[1].resize(n);
    cout << "Enter data:" << endl;
    for(auto i = 0; i < n; ++i){
        cin >> data[0][i] >> data[1][i]; // entering x and y
    }
    SquareAproximation(data);
    LinearApproximation(data);
}