#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double degToRad(double deg) {
	return deg * M_PI / 180;
}

double radToDeg(double rad) {
	return rad * 180 / M_PI;
}

double inv(double alpha_deg) {
	return tan(degToRad(alpha_deg)) - degToRad(alpha_deg);
}

// 中心距变动系数 y
double calcCenterDistanceVariationCoeffivient(double z1, double z2, double m, double a) {
	return a / m - (z1 + z2) / 2;
}

// 啮合压力角 meshing_alpha_deg
double calcMeshingPressureAngle(double z1, double z2, double alpha_deg, double y) {
	double alpha_rad = degToRad(alpha_deg);
	return radToDeg(acos(cos(alpha_rad) / (2 * y / (z1 + z2) + 1)));
}

double sumX(double z1, double z2, double alpha_deg, double meshing_alpha_deg) {
	double inv_alpha = inv(alpha_deg);
	double inv_meshing_alpha = inv(meshing_alpha_deg);
	cout << "-- " << inv_alpha << " --" << endl;
	cout << "-- " << inv_meshing_alpha << " --" << endl;
	return (z1 + z2) * (inv_meshing_alpha - inv_alpha) / 2 / tan(degToRad(alpha_deg));
}

void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}




int main() {

	int m = 3;
	double alpha_deg = 20;
	double z1 = 12, z2 = 24;
	double x1 = 0.6, x2 = 0.36;
	double a = 56.4999;
	double y = calcCenterDistanceVariationCoeffivient(z1, z2, m, a);
	double meshing_alpha_deg = calcMeshingPressureAngle(z1, z2, alpha_deg, y);
	double sumx = sumX(z1, z2, alpha_deg, meshing_alpha_deg);


	print("y", y);
	print("meshing_alpha_deg", meshing_alpha_deg);
	print("sumx", sumx);

	return 0;
}