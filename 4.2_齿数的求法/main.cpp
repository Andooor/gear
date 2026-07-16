#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


// 齿数的和  Sum of the number of teeth
// a: 中心距  m: 模数
double calcSumNumberTeeth(double a, int m) {
	return 2 * a / m;
}

// 齿数  number of teeth
// sumZ: 齿数和  i: 传动比
void calcNumTeeth(double sumZ, double i, double* z) {
	z[0] = sumZ / (i + 1);
	z[1] = sumZ * i / (i + 1);
}

void printNumTeeth(const double* z) {
	cout << left << setw(8) << "z1" << " = " << z[0] << endl;
	cout << left << setw(8) << "z2" << " = " << z[1] << endl;
}

int main() {
	double sumZ = calcSumNumberTeeth(54.000, 3);
	double* z = new double[2];
	calcNumTeeth(sumZ, 1.25, z);

	cout << left << setw(8) << "z1 + z2" << " = " << sumZ << endl;
	printNumTeeth(z);
	return 0;
}