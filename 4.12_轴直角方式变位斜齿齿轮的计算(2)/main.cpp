#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/*

中心距变动系数 Center distance variation coefficient
端面啮合压力角 End face meshing pressure angle
变位系数的和 Sum of displacement coefficients

*/


double degToRad(const double deg) {
	return deg * M_PI / 180;
}

double radToDeg(const double rad) {
	return rad / M_PI * 180;
}
double inv(const double alpha_deg) {
	return tan(degToRad(alpha_deg)) - degToRad(alpha_deg);
}

// 中心距变动系数 Center distance variation coefficient
double calcCenterDistanceVariationCoefficient(const double a, const double m_t, const double z1, const double z2) {
	return a / m_t - (z1 + z2) / 2;
}

// 端面啮合压力角 End face meshing pressure angle
double calcEndFaceMeshingPressureAngle(const double alpha_t_deg, const double y, const double z1, const double z2) {
	double alpha_t_rad = degToRad(alpha_t_deg);
	double tmp_rad = acos(cos(alpha_t_rad) / (2 * y / (z1 + z2) + 1));
	return radToDeg(tmp_rad);
}

// 变位系数的和 Sum of displacement coefficients
double calcSumXn(const double z1, const double z2, const double meshing_alpha_t_deg, const double alpha_t_deg) {
	double alpha_t_rad = degToRad(alpha_t_deg);
	return (z1 + z2) * (inv(meshing_alpha_t_deg) - inv(alpha_t_deg)) / 2 / tan(alpha_t_rad);
}

void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}



int main() {

	double m_t = 3;
	double alpha_t_deg = 20;
	double beta_deg = 30;
	double z1 = 12, z2 = 60;
	double a = 109;
	double y = calcCenterDistanceVariationCoefficient(a, m_t, z1, z2);
	double meshing_alpha_t_deg = calcEndFaceMeshingPressureAngle(alpha_t_deg, y, z1, z2);
	double sumX = calcSumXn(z1, z2, meshing_alpha_t_deg, alpha_t_deg);

	print("y", y);
	print("meshing_alpha_t_deg", meshing_alpha_t_deg);
	print("sumX", sumX);

	return 0;
}