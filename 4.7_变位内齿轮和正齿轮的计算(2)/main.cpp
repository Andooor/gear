#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/*

中心距变动系数  Center distance variation coefficient
啮合压力角	meshing pressure angle
变位系数的差  subtractY

*/

double degToRad(double deg) {
	return deg * M_PI / 180;
}

double radToDeg(double rad) {
	return rad / M_PI * 180;
}

double inv(double alpha_deg) {
	return tan(degToRad(alpha_deg)) - degToRad(alpha_deg);
}

double calcCenterDistanceVariationCoefficient(double a, double m, double z1, double z2){
	return a / m - (z2 - z1) / 2;
}

double calcMeshingPressureAngle(double alpha_deg, double y, double z1, double z2){
	double b = cos(degToRad(alpha_deg)) / (2 * y / (z2 - z1) + 1);
	return radToDeg(acos(b));
}

double subX(double alpha_deg, double meshing_alpha_deg, double z1, double z2) {
	return (z2 - z1) * (inv(meshing_alpha_deg) - inv(alpha_deg)) / 2 / tan(degToRad(alpha_deg));
}

void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}



int main() {

	double m = 3;
	double alpha_deg = 20;
	double z1 = 16, z2 = 24;
	double a = 13.1683;

	double y = calcCenterDistanceVariationCoefficient(a, m, z1, z2);
	double meshing_alpha_deg = calcMeshingPressureAngle(alpha_deg, y, z1, z2);
	double sub_x = subX(alpha_deg, meshing_alpha_deg, z1, z2);

	print("y", y);
	print("meshing_alpha_deg", meshing_alpha_deg);
	print("sub_x", sub_x);

	return 0;
}

